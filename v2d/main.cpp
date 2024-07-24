#include <Windows.h>
#include <windowsx.h>
#include <future>
#include <DxLib.h>
#include "Initializer.h"
#include "Sprite.h"
#include "Setting.h"
#include "define.h"
#include "speaker.h"
#include "vector.h"
using namespace std;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    
    try { Initializer::DxLib(); }
    catch(...){
        MessageBoxA(NULL, "DxLibの初期化に失敗しました。\nDirectX9以降をインストールしてください。",APP_NAME, MB_OK);
        return -1;
    }
    SetWindowLongPtr(GetMainWindowHandle(), GWLP_WNDPROC, (LONG_PTR)SpeakerAddProc);

    #pragma region 変数宣言

    int BodyImage, HeadImage, EyeImage, MouthImage, MouthCloseImage,
        nl, MouseX, MouseY, ep, now, tick = 0;
    Sprite body, head, eye1, eye2, mouth;
    double so = 0, tDeg = 0, md;
    bool isclose;
    vct2d Mouse;
    Setting stg;

    #pragma endregion

    vtubeloop:;

    #pragma region 初期化
    clsDx();
    Initializer::Image(BodyImage, HeadImage, EyeImage, MouthImage, MouthCloseImage);
    stg = *(new Setting());
    if (!stg.isInitialized) goto vtubeloop;
    now = GetNowCount();
    nl = HEIGHT - stg.HeadY;
    ep = HEIGHT - stg.EyePos;
    isclose = true;

    body = Sprite(BodyImage,
        vct2d(WIDTH / 2, stg.BodyY),
        vct2d(0, stg.BodyCentY),
        stg.BodySize);

    head = Sprite(HeadImage,
        vct2d(), vct2d(0, stg.neckY),
        stg.HeadSize);

    eye1 = Sprite(EyeImage,
        vct2d(), vct2d(),
        stg.EyeSize);

    eye2 = Sprite(EyeImage,
        vct2d(), vct2d(),
        stg.EyeSize, true);

    mouth = Sprite(MouthImage,
        vct2d(), vct2d(), 7);
    #pragma endregion

    while (CheckHitKey(KEY_INPUT_F5)); //リセットループ防止
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_END) == 0) {
        tick++;
        if (CheckHitKey(KEY_INPUT_F5) || isNeedReload) {
            isNeedReload = false;
            DeleteGraph(BodyImage);
            DeleteGraph(HeadImage);
            DeleteGraph(EyeImage);
            DeleteGraph(MouthImage);
            goto vtubeloop;
        }
        ClearDrawScreen();
        DrawBox(0, 0, WIDTH, HEIGHT, stg.backgroundColor, 1);
        GetMousePoint(&MouseX, &MouseY);

        #pragma region 体

        if (stg.GetdownMode) {
            body.Pos = vct2d(rand() % WIDTH, rand() % HEIGHT);
            body.Deg = rand() % 360;
            head.Pos = vct2d(rand() % WIDTH, rand() % HEIGHT);
            head.Deg = rand() % 360;
            eye1.Pos = vct2d(rand() % WIDTH, rand() % HEIGHT);
            eye1.Deg = rand() % 360;
            eye2.Pos = vct2d(rand() % WIDTH, rand() % HEIGHT);
            eye2.Deg = rand() % 360;
            mouth.Pos = vct2d(rand() % WIDTH, rand() % HEIGHT);
            mouth.Deg = rand() % 360;
            goto draw;
        }

        so = (double)stg.FureSpeed / 1000 * tick;

        tDeg = sin(so) * stg.BodyFurehaba;
        head.Deg = sin(so -1) * stg.HeadFurehaba;
        body.Deg = tDeg;
        Mouse = vct2d(MouseX - stg.PointerHoseX, 
                    MouseY - stg.PointerHoseY)
                    / stg.HeadPointerSize;

        head.Pos = TurnV(
                vct2d(WIDTH / 2, HEIGHT) + Mouse,
                vct2d(0, nl), tDeg);

        eye1.Deg = head.Deg + stg.EyeKankaku;
        eye1.Pos = TurnV(
            vct2d(head.Pos + Mouse),
            vct2d(0, ep),
            head.Deg + stg.EyeKankaku);

        eye2.Deg = head.Deg - stg.EyeKankaku;
        eye2.Pos = TurnV(
            vct2d(head.Pos + Mouse),
            vct2d(0, ep),
            head.Deg - stg.EyeKankaku);

        #pragma endregion

        #pragma region 瞬き
        md = tick % stg.MabatakiKankaku;
        if (md < stg.MabatakiTime) {
            if (md < stg.MabatakiTime / 2) {
                md = (double)(1 - (double)stg.MabatakiSize / 100) / (stg.MabatakiTime / 2) * (stg.MabatakiTime / 2 - md) + (double)stg.MabatakiSize / 100;
                eye1.Stren = vct2d(1, md);
            }
            else {

                md = (double)(1 - (double)stg.MabatakiSize / 100) / (stg.MabatakiTime / 2) * (md - stg.MabatakiTime / 2) + (double)stg.MabatakiSize / 100;
                eye1.Stren = vct2d(1, md);
            }
        }
        else {

            eye1.Stren = vct2d(1, 1);
        }
        eye2.Stren = eye1.Stren;
        #pragma endregion

        #pragma region 口

        mouth.Stren = vd.Loop(isclose);
        if (isclose) {
            mouth.Stren = mouth.Stren * stg.CloseMouthSize / 100;
        }
        else {
            mouth.Stren = mouth.Stren * stg.MouthSize / 100;
        }
        mouth.Image = isclose ? MouthCloseImage : MouthImage;
        mouth.Pos = TurnV(vct2d(head.Pos + Mouse * stg.MouthPointerSize / 100),
            vct2d(0, stg.MouthY), head.Deg);
        mouth.Deg = head.Deg;

        #pragma endregion

        draw:
        head.Draw();
        body.Draw();
        eye1.Draw();
        eye2.Draw();
        mouth.Draw();
        ScreenFlip();
    }

    DeleteGraph(BodyImage);
    DeleteGraph(HeadImage);
    DeleteGraph(EyeImage);
    DeleteGraph(MouthImage);
    DxLib_End();
    return 0;
}

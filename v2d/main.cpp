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

    int BodyImage, HeadImage, EyeImage, MouthImage,
        resflag, nl, MouseX, MouseY, ep, now;
    Sprite body, head, eye1, eye2, mouth;
    double so, tDeg, md;
    ULONG64 tick;
    vct2d Mouse;
    Setting stg;

    #pragma endregion

    
    vtubeloop:;

    #pragma region 初期化
    Initializer::Image(BodyImage, HeadImage, EyeImage, MouthImage);
    stg = *(new Setting());
    so = 0;
    now = GetNowCount();
    tDeg = 0;
    nl = HEIGHT - stg.HeadY;
    ep = HEIGHT - stg.EyePos;
    MouseX = 0;
    MouseY = 0;
    tick = 0;
    resflag = 0;

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
        vct2d(), vct2d(),
        7);
    #pragma endregion

    while (CheckHitKey(KEY_INPUT_F5)); //リセットループ防止
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_END) == 0) {
        while (now < GetNowCount() - 16) {
            now += 16;
            tick++;
            mouth.Stren = vd.Loop();
            so += (double)stg.FureSpeed / 1000;
        }
        #pragma region DxLib描画系
        if (CheckHitKey(KEY_INPUT_F5)) {
            DeleteGraph(BodyImage);
            DeleteGraph(HeadImage);
            DeleteGraph(EyeImage);
            DeleteGraph(MouthImage);
            goto vtubeloop;
        }
        ClearDrawScreen();
        DrawBox(0, 0, WIDTH, HEIGHT, stg.backgroundColor, 1);
        GetMousePoint(&MouseX, &MouseY);


        tDeg = sin(so) * stg.BodyFurehaba;
        head.Deg = sin(so -1) * stg.HeadFurehaba;
        if (stg.GetdownMode) {
            head.Deg = rand() % 360;
            tDeg = rand() % 360;
            body.Pos.x = rand() % WIDTH;
            body.Pos.y = rand() % HEIGHT;
        }
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

        //瞬き
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

        mouth.Pos = TurnV(vct2d(head.Pos + Mouse * 0.8),
            vct2d(0, 66), head.Deg);
        mouth.Deg = head.Deg;

        head.Draw();
        body.Draw();
        eye1.Draw();
        eye2.Draw();
        mouth.Draw();
        ScreenFlip();
        #pragma endregion
        
    }

    DeleteGraph(BodyImage);
    DeleteGraph(HeadImage);
    DeleteGraph(EyeImage);
    DeleteGraph(MouthImage);
    DxLib_End();
    return 0;
}

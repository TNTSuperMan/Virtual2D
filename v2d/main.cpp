#include <Windows.h>
#include <future>
#include <DxLib.h>
#include "Initializer.h"
#include "Sprite.h"
#include "Setting.h"
#include "define.h"
#include "getvoice.h"
#include "vector.h"
using namespace std;
MSG msg;
bool ended;
BOOL value;


BOOL RegisterApp(const char* windowID, WNDPROC windowProc) {
    WNDCLASSEXA wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hIcon = (HICON)LoadIconA(NULL, IDI_APPLICATION);
    wc.hCursor = (HCURSOR)LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = windowID;
    wc.hIconSm = (HICON)LoadImageA(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
    return (RegisterClassExA(&wc));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND inp, btn;
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CREATE:
            inp = CreateWindow(
                "EDIT", "ohayou gozaimasu.",
                WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT,
                0, 0, 325, 30, hWnd, (HMENU)1, ((LPCREATESTRUCT)(lp))->hInstance, NULL
            );
            btn = CreateWindow(
                "BUTTON", "発声",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                325, 0, 60, 30, hWnd, (HMENU)2, ((LPCREATESTRUCT)(lp))->hInstance, NULL
            );
            return 0;
        case WM_COMMAND:
            if (LOWORD(wp) == 2) {
                SetWindowText(btn, "生成中");
                char* inpt = new char[255];
                GetWindowText(inp, inpt, 255);
                Say(inpt);
                return 0;
            }
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    
    try { Initializer::DxLib(); }
    catch(...){
        MessageBoxA(NULL, "DxLibの初期化に失敗しました。\nDirectX9以降をインストールしてください。",APP_NAME, MB_OK);
        return -1;
    }

    #pragma region 変数宣言

    int BodyImage, HeadImage, EyeImage, MouthImage,
        resflag, nl, MouseX, MouseY, ep;
    Sprite body, head, eye1, eye2;
    double so, tDeg, md;
    ULONG64 tick;
    vct2d Mouse;
    HWND wind;
    Setting stg;
    thread* t = new thread([] {return; });

    #pragma endregion

    /*
    #pragma region 発声ウインドウの初期化

    ended = false;

    if (!RegisterApp(VOICEWIND_ID, WndProc)) return -1;

    wind = CreateWindow(
        VOICEWIND_ID, "発声ウインドウ",
        (WS_OVERLAPPED |
            WS_CAPTION |
            WS_SYSMENU |
            WS_THICKFRAME |
            WS_MINIMIZEBOX),
        0, 0, 400, 67, GetMainWindowHandle(),
        NULL, hInstance, NULL
    );

    ShowWindow(wind,SW_SHOW);
    UpdateWindow(wind);

    #pragma endregion
    */
    vtubeloop:;

    #pragma region 初期化
    Initializer::Image(BodyImage, HeadImage, EyeImage, MouthImage);
    stg = *(new Setting());
    so = 0;
    tDeg = 0;
    nl = HEIGHT - stg.HeadY;
    ep = HEIGHT - stg.EyePos;
    MouseX = 0;
    MouseY = 0;
    tick = 0;
    resflag = 0;

    body = *(new Sprite(BodyImage,
        vct2d(WIDTH / 2, stg.BodyY),
        vct2d(0, stg.BodyCentY),
        stg.BodySize));

    head = *(new Sprite(HeadImage,
        vct2d(), vct2d(0, stg.neckY),
        stg.HeadSize));

    eye1 = *(new Sprite(EyeImage,
        vct2d(), vct2d(),
        stg.EyeSize));

    eye2 = *(new Sprite(EyeImage,
        vct2d(), vct2d(),
        stg.EyeSize, true));
    #pragma endregion

    while (CheckHitKey(KEY_INPUT_F5)); //リセットループ防止
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_END) == 0) {
        tick++;
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
        so += (double)stg.FureSpeed / 1000;


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
                eye2.Stren = vct2d(1, md);
            }
            else {

                md = (double)(1 - (double)stg.MabatakiSize / 100) / (stg.MabatakiTime / 2) * (md - stg.MabatakiTime / 2) + (double)stg.MabatakiSize / 100;
                eye1.Stren = vct2d(1, md);
                eye2.Stren = vct2d(1, md);
            }
        }
        else {

            eye1.Stren = vct2d(1, 1);
            eye2.Stren = vct2d(1, 1);
        }

        head.Draw();
        body.Draw();
        eye1.Draw();
        eye2.Draw();
        ScreenFlip();
        #pragma endregion

        /*
        #pragma region 発声ウインドウ

        if (t->joinable() && !ended) t = new thread([] {
            value = GetMessageA(&msg, NULL, 0, 0);
            if (value == 0 || value == -1) {
                ended = true;
                return;
            }

            TranslateMessage(&msg);
            DispatchMessageA(&msg);
            });
        #pragma endregion
        */
    }

    DeleteGraph(BodyImage);
    DeleteGraph(HeadImage);
    DeleteGraph(EyeImage);
    DeleteGraph(MouthImage);
    //DestroyWindow(wind);
    DxLib_End();
    return 0;
}

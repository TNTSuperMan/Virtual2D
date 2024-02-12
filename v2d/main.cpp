#include "include.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    
    try { Initializer::DxLib(); }
    catch(...){
        MessageBoxA(NULL, "DxLibの初期化に失敗しました。\nDirectX9以降をインストールしてください。",APP_NAME, MB_OK);
        return -1;
    }

    int BodyImage, HeadImage, EyeImage, MouthImage, resflag;

vtubeloop:;

    Initializer::Image(BodyImage, HeadImage, EyeImage, MouthImage);
    Setting stg = *(new Setting());
    double so = 0;
    TCHAR* debug = new TCHAR[255];
    double tDeg = 0;
    int nl = HEIGHT - stg.HeadY;
    int MouseX = 0;
    int MouseY = 0;
    vector Mouse;
    resflag = 0;

    Sprite* body = new Sprite(BodyImage,
        vector(WIDTH / 2, stg.BodyY),
        vector(0, stg.BodyCentY), vector(1, 1),
        stg.BodySize, 0);

    Sprite* head = new Sprite(HeadImage,
        vector(WIDTH / 2, stg.HeadY),
        vector(0, stg.neckY),
        vector(1, 1), stg.HeadSize, 0);

    Sprite* eye1 = new Sprite(EyeImage,
        vector(0,0),
        vector(0,0), vector(1, 1), stg.EyeSize, 0);

    Sprite* eye2 = new Sprite(EyeImage,
        vector(0,0),
        vector(0,0), vector(1, 1), stg.EyeSize, 0, true);
    

    while (CheckHitKey(KEY_INPUT_R));
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_END) == 0) {
        if (CheckHitKey(KEY_INPUT_R)) {
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
        head->Rotate = sin(so -1) * stg.HeadFurehaba;
        if (stg.GetdownMode) {
            head->Rotate = rand() % 360;
            tDeg = rand() % 360;
            body->Pos.x = rand() % WIDTH;
            body->Pos.y = rand() % HEIGHT;
        }
        body->Rotate = tDeg;
        Mouse = vector((double)(MouseX - stg.PointerHoseX) / stg.HeadPointerSize,
            (double)(MouseY - stg.PointerHoseY) / stg.HeadPointerSize);
        
        head->Pos = vector(
            sin(tDeg * A_DEG),
            -cos(tDeg * A_DEG)) * 
            (double)nl + vector(WIDTH / 2,HEIGHT) + Mouse;

        Mouse = vector((double)(MouseX - stg.PointerHoseX) / stg.EyePointerSize,
                       (double)(MouseY - stg.PointerHoseY) / stg.EyePointerSize);

        eye1->Pos = vector(
            sin((head->Rotate + stg.EyeKankaku) * A_DEG),
            -cos((head->Rotate + stg.EyeKankaku) * A_DEG)) *
            (HEIGHT - stg.EyePos) + head->Pos + Mouse;

        eye2->Pos = vector(
            sin((head->Rotate - stg.EyeKankaku) * A_DEG),
            -cos((head->Rotate - stg.EyeKankaku) * A_DEG)) *
            (HEIGHT - stg.EyePos) + head->Pos + Mouse;

        eye1->Rotate = head->Rotate + stg.EyeKankaku;
        eye2->Rotate = head->Rotate - stg.EyeKankaku;


        head->Draw();
        body->Draw();
        eye1->Draw();
        eye2->Draw();
        ScreenFlip();
    }

    DeleteGraph(BodyImage);
    DeleteGraph(HeadImage);
    DeleteGraph(EyeImage);
    DeleteGraph(MouthImage);
    DxLib_End();
    return 0;
}

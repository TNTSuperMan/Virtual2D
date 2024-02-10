#include "include.h"

void InitializeDxLib() {
    if (DxLib_Init() == -1) throw;
    ChangeWindowMode(1);
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWindowSizeExtendRate(1);
    SetWaitVSyncFlag(1);
    SetUseTransColor(0);
    SetAlwaysRunFlag(1);
    SetWindowText(APP_NAME_L);
    SetDoubleStartValidFlag(1);
    SetMainWindowClassName(L"Virtual2D_Vtuber_Application");
    SetMouseDispFlag(1);
    SetDrawScreen(DX_SCREEN_BACK);
}

void InitializeImage(int &BodyImage, int &HeadImage, int &EyesImage, int &MouthImage){
    BodyImage = LoadGraph(L".\\model\\body.png");
    HeadImage = LoadGraph(L".\\model\\head.png");
    EyesImage = LoadGraph(L".\\model\\eyes.png");
    MouthImage = LoadGraph(L".\\model\\mouth.png");
    if (BodyImage == -1) MessageBoxA(NULL, ".\\model\\body.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (HeadImage == -1) MessageBoxA(NULL, ".\\model\\head.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (EyesImage == -1) MessageBoxA(NULL, ".\\model\\eyes.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (MouthImage == -1) MessageBoxA(NULL, ".\\model\\mouth.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow){
    try{InitializeDxLib();}
    catch(...){
        MessageBoxA(NULL, "DxLibの初期化に失敗しました。\nDirectXを確認してください。",APP_NAME, MB_OK);
        return -1;
    }

    int BodyImage, HeadImage, EyesImage, MouthImage;
    InitializeImage(BodyImage, HeadImage, EyesImage, MouthImage);


    Sprite* s = new Sprite(BodyImage, vector(250, 500), vector(0, -125), vector(1, 1), 25, 0);
    double so = 0;
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();
        DrawBox(0, 0, WIDTH, HEIGHT, GetColor(255, 255, 0), 1);
        so += 0.05;
        s->Rotate = sin(so) * 30;
        s->Draw();
        
        ScreenFlip();
    }

    DeleteGraph(BodyImage);
    DeleteGraph(HeadImage);
    DeleteGraph(EyesImage);
    DeleteGraph(MouthImage);
    
    DxLib_End();
    return 0;
}

#include "Initializer.h"

void Initializer::DxLib() {
    SetOutApplicationLogValidFlag(0);
    SetWindowText(L"起動中...");
    ChangeWindowMode(1);
    if (DxLib_Init() == -1) throw;
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWindowIconID(101);
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
void Initializer::Image(int& BodyImage, int& HeadImage, int& EyeImage, int& MouthImage) {
    BodyImage = LoadGraph(L".\\model\\body.png");
    HeadImage = LoadGraph(L".\\model\\head.png");
    EyeImage = LoadGraph(L".\\model\\eye.png");
    //MouthImage = LoadGraph(L".\\model\\mouth.png");
    if (BodyImage == -1) MessageBoxA(NULL, ".\\model\\body.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (HeadImage == -1) MessageBoxA(NULL, ".\\model\\head.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (EyeImage == -1) MessageBoxA(NULL, ".\\model\\eye.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    //if (MouthImage == -1) MessageBoxA(NULL, ".\\model\\mouth.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
}

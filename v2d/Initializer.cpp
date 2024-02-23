#include "Initializer.h"


void Initializer::DxLib() {
    SetOutApplicationLogValidFlag(0);
    SetWindowText("起動中...");
    ChangeWindowMode(1);
    if (DxLib_Init() == -1) throw;
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWindowIconID(101);
    SetWindowSizeExtendRate(1);
    SetWaitVSyncFlag(1);
    SetUseTransColor(0);
    SetAlwaysRunFlag(1);
    SetWindowText(APP_NAME);
    SetDoubleStartValidFlag(1);
    SetMainWindowClassName("Virtual2D_Vtuber_Application");
    SetMouseDispFlag(1);
    SetDrawScreen(DX_SCREEN_BACK);
}
void Initializer::Image(int& BodyImage, int& HeadImage, int& EyeImage, int& MouthImage) {
    BodyImage = LoadGraph(".\\model\\body.png");
    HeadImage = LoadGraph(".\\model\\head.png");
    EyeImage = LoadGraph(".\\model\\eye.png");
    //MouthImage = LoadGraph(L".\\model\\mouth.png");
    if (BodyImage == -1) MessageBoxA(NULL, ".\\model\\body.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (HeadImage == -1) MessageBoxA(NULL, ".\\model\\head.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    if (EyeImage == -1) MessageBoxA(NULL, ".\\model\\eye.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
    //if (MouthImage == -1) MessageBoxA(NULL, ".\\model\\mouth.pngにアクセスできません。\n無視して続行します。", APP_NAME, MB_OK);
}

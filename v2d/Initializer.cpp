#include "Initializer.h"


void Initializer::DxLib() {
    SetOutApplicationLogValidFlag(0);
    SetWindowText("起動中...");
    ChangeWindowMode(1);
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWaitVSyncFlag(1);
    if (DxLib_Init() == -1) throw;
    SetWindowIconID(101);
    SetWindowSizeExtendRate(1);
    SetUseTransColor(0);
    SetAlwaysRunFlag(1);
    SetWindowText(APP_NAME);
    SetDoubleStartValidFlag(0);
    SetMainWindowClassName(APP_CLASS);
    SetMouseDispFlag(1);
    SetDrawScreen(DX_SCREEN_BACK);
}
void Initializer::Image(int& BodyImage, int& HeadImage, int& EyeImage, int& MouthImage, int& MouthCloseImage) {
    BodyImage = LoadGraph(".\\model\\body.png");
    HeadImage = LoadGraph(".\\model\\head.png");
    EyeImage = LoadGraph(".\\model\\eye.png");
    MouthImage = LoadGraph(".\\model\\mouth.png");
    MouthCloseImage = LoadGraph(".\\model\\mouth_close.png");
    if (BodyImage == -1) Dialog(".\\model\\body.pngにアクセスできません。\n無視して続行します。");
    if (HeadImage == -1) Dialog(".\\model\\head.pngにアクセスできません。\n無視して続行します。");
    if (EyeImage == -1) Dialog(".\\model\\eye.pngにアクセスできません。\n無視して続行します。");
    if (MouthImage == -1) Dialog(".\\model\\mouth.pngにアクセスできません。\n無視して続行します。");
    if (MouthCloseImage == -1) Dialog(".\\model\\mouth_close.pngにアクセスできません。\n無視して続行します。");
}

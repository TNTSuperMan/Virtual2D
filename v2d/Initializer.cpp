#include "Initializer.h"


void Initializer::DxLib() {
    SetOutApplicationLogValidFlag(0);
    SetWindowText("�N����...");
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
    if (BodyImage == -1) MessageBoxA(NULL, ".\\model\\body.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (HeadImage == -1) MessageBoxA(NULL, ".\\model\\head.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (EyeImage == -1) MessageBoxA(NULL, ".\\model\\eye.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (MouthImage == -1) MessageBoxA(NULL, ".\\model\\mouth.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (MouthCloseImage == -1) MessageBoxA(NULL, ".\\model\\mouth_close.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
}

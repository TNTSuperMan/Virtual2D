#include "Initializer.h"

void Initializer::DxLib() {
    SetOutApplicationLogValidFlag(0);
    SetWindowText(L"�N����...");
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
    if (BodyImage == -1) MessageBoxA(NULL, ".\\model\\body.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (HeadImage == -1) MessageBoxA(NULL, ".\\model\\head.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    if (EyeImage == -1) MessageBoxA(NULL, ".\\model\\eye.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
    //if (MouthImage == -1) MessageBoxA(NULL, ".\\model\\mouth.png�ɃA�N�Z�X�ł��܂���B\n�������đ��s���܂��B", APP_NAME, MB_OK);
}

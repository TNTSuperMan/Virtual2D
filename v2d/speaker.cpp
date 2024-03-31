#include "speaker.h"

string vpath;
VoiceData vd;

LRESULT CALLBACK SpeakerAddProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND inp, btn;
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0; break;
    case 0xBACA:
        switch (wp) {
        case 0:
            return 1248; break;
        case 1:
            vd = VoiceData();
            vpath.clear();
            break;
        case 2:
            vpath.append((char*)&lp);
            break;
        case 3:
            //MessageBox(GetMainWindowHandle(), vpath.c_str(), APP_NAME, MB_OK);
            PlaySoundFile(vpath.c_str(), DX_PLAYTYPE_BACK);
            break;
        }
        return 0; break;
    case 0xBAFA:
        vd.Add(lp, wp);
        return 0; break;
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

VoiceData::VoiceData() {
    waittime = vector<int>();
    saydata = vector<char>();
    isstart = false;
    tick = 0;
}

void VoiceData::Add(int wait, char say) {
    waittime.push_back(wait);
    saydata.push_back(say);
}

vct2d VoiceData::Loop() {
    if (isstart) {
        /* Œû‚ÌŒ`‚ðŒvŽZ */
        vct2d ret = vct2d(1,1);
        tick++;
        return ret;
    }
    else {
        return vct2d(1, (double)(rand() % 100) / 100);
    }
}

void VoiceData::Start() {
    isstart = true;
}
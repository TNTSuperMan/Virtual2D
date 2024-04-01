#include "speaker.h"
#define Mouth(type,width,height) case type:ret=vct2d(width,height);break;
using json = nlohmann::json;

string vpath;
string audioquery;
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
            audioquery.clear();
            vpath.clear();
            break;
        case 2:
            vpath.append((char*)&lp);
            break;
        case 3:
            audioquery.append((char*)&lp);
            break;
        case 4:
            json query = json::parse(audioquery);
            string ret;
            for each ( json ap in query["accent_phrases"])
            {
                for each (json mora in ap["moras"])
                {
                    if (mora["consonant"].is_string()) {
                        vd.Add(mora["consonant_length"].get<double>() * 60, 
                            *(mora["consonant"].get<string>().c_str()));
                    }
                    vd.Add(mora["vowel_length"].get<double>() * 60,
                        *(mora["vowel"].get<string>().c_str()));
                }
            }
            vd.waitsum = 0;
            for each (int var in vd.waittime)
            {
                vd.waitsum += var;
            }
            PlaySoundFile(vpath.c_str(), DX_PLAYTYPE_BACK);
            printfDx(ret.c_str());
            vd.Start();
            break;
        }
        return 0; break;
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

VoiceData::VoiceData() {
    waittime = vector<int>();
    saydata = vector<char>();
    isplay = false;
    tick = 0;
}

void VoiceData::Add(int wait, char say) {
    waittime.push_back(wait);
    saydata.push_back(say);
}

vct2d VoiceData::Loop(bool& isclose) {
    if (isplay) {
        /* Œû‚ÌŒ`‚ðŒvŽZ */
        vct2d ret = vct2d(1,1);
        if (!CheckSoundFile()) {
            isplay = false;
            isclose = true;
            return vct2d(1, 1);
        }
        ULONG sum = 0;
        int i = -1;
        if (waitsum <= tick) {
            isclose = true;
            return vct2d(1, 1);
        }
        do
        {
            i++;
            sum += waittime[i];
        } while (sum < tick);
        switch (saydata[i]) {
            Mouth('a', 1.5, 1);
            Mouth('i', 1.2, 0.5);
            Mouth('u', 0.8, 1);
            Mouth('e', 1.55, 0.85);
            Mouth('o', 1.3, 1.3);
            Mouth('k', 1.1, 0.7);
            Mouth('s', 1.4, 0.55);
            Mouth('t', 1.2, 0.3);
            Mouth('n', 1.1, 0.2);
            Mouth('h', 1.4, 0.6);
            Mouth('m', 0.8, 0.2);
            Mouth('y', 1.15, 0.35);
            Mouth('w', 1.1, 0.45);
            Mouth('g', 0.9, 0.55);
            Mouth('z', 1.15, 0.55);
            Mouth('d', 1.2, 0.2);
            Mouth('p', 0.75, 0.3);
        }
        tick++;
        isclose = false;
        return ret;
        //return vct2d(1, (double)(rand() % 100) / 100);
    }
    else {
        tick = 0;
        isclose = true;
        return vct2d(1,1);
    }
}

void VoiceData::Start() {
    isplay = true;
}
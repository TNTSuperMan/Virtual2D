#include "speaker.hpp"
#define Mouth(type,width,height) case type:ret=vct2d(width,height);break;
using json = nlohmann::json;

string vpath;
string querypath;
int len;
VoiceData vd;
bool isNeedReload = false;

LRESULT CALLBACK SpeakerAddProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0; break;
    case 0xBACA:
        switch (wp) {
        case 0: //Test
            return 1248; break;
        case 1: //Init
            vd = VoiceData();
            querypath.clear();
            vpath.clear();
            break;
        case 2: //VoicePath
            vpath.append((char*)&lp);
            break;
        case 3: //QueryPath
            querypath.append((char*)&lp);
            break;
        case 4: //Length
            len = lp + 2;
            break;
        case 5: //Say
            ifstream f(querypath);
            char* jsondata = new char[len];
            f.getline(jsondata, len);
            f.close();
            json query = json::parse(jsondata);
            int i = 0;
            while (query["accent_phrases"][i].is_structured()) {
                int j = 0;
                while (query["accent_phrases"][i]["moras"][j].is_structured()) {
                    json mora = query["accent_phrases"][i]["moras"][j];
                    if (mora["consonant"].is_string()) {
                        vd.Add(mora["consonant_length"].get<double>() * 60,
                            *(mora["consonant"].get<string>().c_str()));
                    }
                    vd.Add(mora["vowel_length"].get<double>() * 60,
                        *(mora["vowel"].get<string>().c_str()));
                    j++;
                }
                i++;
            }
            vd.waitsum = 0;
            for (int i = 0; i < vd.waittime.size(); i++) {
                vd.waitsum += vd.waittime[i];
            }
            PlaySoundFile(vpath.c_str(), DX_PLAYTYPE_BACK);
            vd.Start();
            break;
        }
        return 0; break;
    case 0xBAFA:
        isNeedReload = true;
        return 4545; break;
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

VoiceData::VoiceData() {
    waittime = vector<int>();
    saydata = vector<char>();
    isplay = false;
    tick = 0;
    waitsum = 0;
}

void VoiceData::Add(int wait, char say) {
    waittime.push_back(wait);
    saydata.push_back(say);
}
vct2d VoiceData::Loop() {
    if (isplay) {
        /* Œû‚ÌŒ`‚ðŒvŽZ */
        vct2d ret = vct2d(1,1);
        if (!CheckSoundFile()) {
            isplay = false;
            return vct2d(1, 1);
        }
        ULONG sum = 0;
        int i = -1;
        if (waitsum <= tick) {
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
        return ret;
    }
    else {
        tick = 0;
        return vct2d(1,1);
    }
}

void VoiceData::Start() {
    isplay = true;
}
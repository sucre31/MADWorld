#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <array>
#include <queue>
#pragma comment(lib, "winmm.lib")
#include "System/Singleton.h"

enum eMidi {
    C_0 = 12, C_S0, D_0, D_S0, E_0, F_0, F_S0, G_0,
    G_S0, A_0, A_S0, B_0,
    C_1 = 24, C_S1, D_1, D_S1, E_1, F_1, F_S1, G_1,
    G_S1, A_1, A_S1, B_1,
    C_2 = 36, C_S2, D_2, D_S2, E_2, F_2, F_S2, G_2,
    G_S2, A_2, A_S2, B_2,
    C_3 = 48, C_S3, D_3, D_S3, E_3, F_3, F_S3, G_3,
    G_S3, A_3, A_S3, B_3,
    C_4 = 60, C_S4, D_4, D_S4, E_4, F_4, F_S4, G_4,
    G_S4, A_4, A_S4, B_4,
    C_5 = 72, C_S5, D_5, D_S5, E_5, F_5, F_S5, G_5,
    G_S5, A_5, A_S5, B_5,
    C_6 = 84, C_S6, D_6, D_S6, E_6, F_6, F_S6, G_6,
    G_S6, A_6, A_S6, B_6,
    C_7 = 96, C_S7, D_7, D_S7, E_7, F_7, F_S7, G_7,
    G_S7, A_7, A_S7, B_7,
    C_8 = 108
};

struct MidiMessage {
    UINT msg;
    DWORD para1;
    DWORD para2;
};

class MIDI final : public Singleton<MIDI>
{
private:
    static const int midiDeviceMax = 3;

    HMIDIIN midiHandle[midiDeviceMax];
    MMRESULT res;
    MIDIINCAPS midiininformation;
    UINT midiresult;
    bool isGetInfoSucces;

    static void CALLBACK MidiInProc(
        HMIDIIN, UINT, DWORD, DWORD, DWORD);

    int  _hold[128][16];        // 押されているフレーム数
    bool _trigger[128][16];     // そのフレームでNOTE_ONが来たか

    static std::queue<MidiMessage> midiQueue;
public:
    MIDI();
    ~MIDI() = default;

    void openMidi(UINT devid, int midiIndex);
    void closeMidi(int midiIndex);
    void update();
    void draw();
    TCHAR* getMidiInfo();

    int get(int note, int channel) const;
    int get(int note) const; // チャンネル無視版
    bool isTrigger(int note, int channel) const;
};
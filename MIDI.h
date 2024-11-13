#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <array>
#pragma comment(lib, "winmm.lib")
#include "Singleton.h"

enum eMidi {
	C_0 = 12, C_S0 = 13, D_0 = 14, D_S0 = 15, E_0 = 16, F_0 = 17, F_S0 = 18, G_0 = 19,
	G_S0 = 20, A_0 = 21, A_S0 = 22, B_0 = 23,
	C_1 = 24, C_S1 = 25, D_1 = 26, D_S1 = 27, E_1 = 28, F_1 = 29, F_S1 = 30, G_1 = 31,
	G_S1 = 32, A_1 = 33, A_S1 = 34, B_1 = 35,
	C_2 = 36, C_S2 = 37, D_2 = 38, D_S2 = 39, E_2 = 40, F_2 = 41, F_S2 = 42, G_2 = 43,
	G_S2 = 44, A_2 = 45, A_S2 = 46, B_2 = 47,
	C_3 = 48, C_S3 = 49, D_3 = 50, D_S3 = 51, E_3 = 52, F_3 = 53, F_S3 = 54, G_3 = 55,
	G_S3 = 56, A_3 = 57, A_S3 = 58, B_3 = 59,
	C_4 = 60, C_S4 = 61, D_4 = 62, D_S4 = 63, E_4 = 64, F_4 = 65, F_S4 = 66, G_4 = 67,
	G_S4 = 68, A_4 = 69, A_S4 = 70, B_4 = 71,
	C_5 = 72, C_S5 = 73, D_5 = 74, D_S5 = 75, E_5 = 76, F_5 = 77, F_S5 = 78, G_5 = 79,
	G_S5 = 80, A_5 = 81, A_S5 = 82, B_5 = 83,
	C_6 = 84, C_S6 = 85, D_6 = 86, D_S6 = 87, E_6 = 88, F_6 = 89, F_S6 = 90, G_6 = 91,
	G_S6 = 92, A_6 = 93, A_S6 = 94, B_6 = 95,
	C_7 = 96, C_S7 = 97, D_7 = 98, D_S7 = 99, E_7 = 100, F_7 = 101, F_S7 = 102, G_7 = 103,
	G_S7 = 104, A_7 = 105, A_S7 = 106, B_7 = 107,
	C_8 = 108
};

class MIDI final : public Singleton<MIDI>
{
private:
	int numMidiDevices;
	static const int midiDeviceMax = 3;
	UINT midiresult;
	HMIDIIN midiHandle[midiDeviceMax];
	MMRESULT res;
	MIDIINCAPS midiininformation;
	bool isGetInfoSucces;
	static void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT MidiMsg, DWORD dwInstance, DWORD dwPara1, DWORD dwPara2);
	static UINT uiResMidiMsg;
	static DWORD dwResPara1;
	static DWORD dwResPara2;
	static bool  MidiInFlag;
	// とりあえずいくつかのキーを監視
	const static int MIDI_KEY_NUM = 109; // 255?
	std::array<int, MIDI_KEY_NUM> _idArray;  //どのボタンがどのボタンに割り当たっているかを示す
	std::array<int, MIDI_KEY_NUM> _midi;      //16ボタンのpad入力状態格納
	int tmpNote;

public:
	MIDI();
	~MIDI() = default;
	void openMidi(UINT, int);
	void closeMidi(int);
	void update();
	void draw();
};


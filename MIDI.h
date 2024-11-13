#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")
#include "Singleton.h"

class MIDI final : public Singleton<MIDI>
{
private:
	int numMidiDevices;
	UINT midiresult;
	MIDIINCAPS midiininformation;
	bool isSucces;
public:
	MIDI();
	~MIDI() = default;
	void draw();
};


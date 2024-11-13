#include<Dxlib.h>
#include <string>
#include "MIDI.h"

MIDI::MIDI() {
	numMidiDevices = midiInGetNumDevs();
	isSucces = false;
	for (int idMIDI = 0; idMIDI < numMidiDevices; idMIDI++)
	{
		//MIDI Inputデバイスの情報
		midiresult = midiInGetDevCaps(idMIDI, &midiininformation, sizeof(MIDIINCAPS));
		if (midiresult != MMSYSERR_NOERROR) {
			isSucces = false;
		}
	}
}

void MIDI::draw() {
	clsDx();
	//printfDx("%d", numMidiDevices);
	//printfDx("%d",isSucces);
	unsigned int Color;

	Color = GetColor(255, 255, 255);
	DrawFormatString(0, 670, Color, "%s", midiininformation.szPname);
}
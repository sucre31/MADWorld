#include<Dxlib.h>
#include <string>
#include "MIDI.h"

UINT MIDI::uiResMidiMsg = 0;
DWORD MIDI::dwResPara1 = 0;
DWORD MIDI::dwResPara2 = 0;
bool MIDI::MidiInFlag = false;


MIDI::MIDI() 
	: numMidiDevices(0), isGetInfoSucces(false) {
	for (int i = 0; i < midiDeviceMax; i++) {
		midiHandle[i] = nullptr;
	}
	isGetInfoSucces = false;
	for (int i = 0; i < eMidi::C_8; i++) {
		_midi[i] = 0;
	}
}

/*
@brief MIDI�f�o�C�X���J���ēo�^����
@param devid �f�o�C�X��id
@param midiIndex �z��ɓo�^����ԍ�
*/
void MIDI::openMidi(UINT devid, int midiIndex) {
	if (midiIndex < midiDeviceMax) {
		isGetInfoSucces = false;
		res = midiInOpen(&midiHandle[midiIndex], devid, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
		if (res != MMSYSERR_NOERROR) {
			printfDx("Cannot open MIDI input device %d\n", devid);
		}
		else {
			// MIDI���͂̊J�n
			midiInStart(midiHandle[midiIndex]);
		}
	}
	else {
		printfDx("Cannot regist MIDI input device %d\n", midiIndex);
	}
	//MIDI Input�f�o�C�X�̏��
	midiresult = midiInGetDevCaps(0u, &midiininformation, sizeof(MIDIINCAPS));
	if (midiresult != MMSYSERR_NOERROR) {
		isGetInfoSucces = false;
	}
	else {
		isGetInfoSucces = true;
	}
}

void MIDI::closeMidi(int midiIndex){
	midiInStop(midiHandle[midiIndex]);
	midiInReset(midiHandle[midiIndex]);
	midiInClose(midiHandle[midiIndex]);
}

void MIDI::update() {
	if (MidiInFlag) {
		//MIDI�̓��͏�Ԃ��擾(dwResPara1�ɂ��낢��͂����Ă�
		unsigned char status = (dwResPara1 & 0x000000ff);
		unsigned char velocity = (dwResPara1 & 0x00ff0000) >> 16;
		unsigned char note = (dwResPara1 & 0x0000ff00) >> 8;
		for (int i = eMidi::A_0; i <= eMidi::C_8; i++) {
			if (_midi[i] > 0) {
				// �����ꑱ���Ă�Ȃ瑝��
				if (_midi[i] < 255) {
					_midi[i]++;
				}
			}
			if (status == 0x90 && note == i && velocity > 0) {
				_midi[i] = 1;
				printfDx("%d ��������܂���\n", i);
			}
			else if (status == 0x80 && note == i || (status == 0x90 && note == i && velocity == 0)) {
				// �����ꂽ����
				_midi[i] = 0;
			}
		}
		MidiInFlag = false;
	}
	else {
		for (int i = eMidi::A_0; i < eMidi::C_8; i++) {
			if (_midi[i] > 0) {
				// �����ꑱ���Ă�Ȃ瑝��
				if (_midi[i] < 255) {
					_midi[i]++;
				}
			}
		}
	}
}


void MIDI::draw() {
	unsigned int Color;
	Color = GetColor(255, 255, 255);
	if (isGetInfoSucces) {
		DrawFormatString(0, 700, Color, "%s", midiininformation.szPname);
	}
	//DrawFormatString(0, 0, Color, "note = %u\n", tmpNote);
}

void CALLBACK MIDI::MidiInProc(HMIDIIN hMidiIn, UINT MidiMsg, DWORD dwInstance, DWORD dwPara1, DWORD dwPara2){
	switch (MidiMsg){

	case MIM_OPEN:
		break;

	case MIM_CLOSE:
		break;
	case MIM_DATA:
		uiResMidiMsg = MidiMsg;
		dwResPara1 = dwPara1;
		dwResPara2 = dwPara2;
		MidiInFlag = true;
		break;
	case MIM_LONGDATA:
		break;
	case MIM_ERROR:
		break;
	case MIM_LONGERROR:
		break;
	case MIM_MOREDATA:
		break;
	default:
		break;
	}
}

/*!
@brief �n���ꂽMIDI�L�[�ԍ��̓��̓t���[������Ԃ�
*/
int MIDI::get(eMidi eID) const
{
	return _midi[eID];
}
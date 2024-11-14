#include<Dxlib.h>
#include <string>
#include "MIDI.h"

std::queue<MidiMessage> MIDI::midiQueue;

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
	for (int i = eMidi::A_0; i < eMidi::C_8; i++) {
		if (_midi[i] > 0) {
			// �����ꑱ���Ă�Ȃ瑝��
			if (_midi[i] < 255) {
				_midi[i]++;
			}
		}
	}
	if (midiQueue.size() > 0) {
		//MIDI�̓��͏�Ԃ��擾(dwResPara1�ɂ��낢��͂����Ă�
		MidiMessage tmpMidiMes = midiQueue.front();
		midiQueue.pop();
		unsigned char status = (tmpMidiMes.para1 & 0x000000ff);
		unsigned char velocity = (tmpMidiMes.para1 & 0x00ff0000) >> 16;
		unsigned char note = (tmpMidiMes.para1 & 0x0000ff00) >> 8;
		// eMidi::A_0 ���� eMidi::C_8 �͈͓̔����`�F�b�N���Ă��珈��
		if (note >= eMidi::A_0 && note <= eMidi::C_8) {
			int i = note;  // �z��̃C���f�b�N�X�ƈ�v����悤�� note �𒼐ڎg�p

			if (status == 0x90 && velocity > 0) {
				// �m�[�g�I�� (�L�[�������ꂽ) �Ƃ��� 1 �ɃZ�b�g
				_midi[i] = 1;
				//printfDx("%d ��������܂���\n", i);
			}
			else if (status == 0x80 || (status == 0x90 && velocity == 0)) {
				// �m�[�g�I�t�܂��̓m�[�g�I���i�x���V�e�B0�j�ŗ����ꂽ�ƌ��Ȃ�
				_midi[i] = 0;
				//printfDx("%d ��������܂���\n", i);
			}
		}
	}
}


void MIDI::draw() {
	unsigned int Color;
	Color = GetColor(255, 255, 255);
	if (isGetInfoSucces) {
		//DrawFormatString(0, 700, Color, "%s", midiininformation.szPname);
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
		midiQueue.push({ MidiMsg, dwPara1, dwPara2 });
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
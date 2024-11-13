#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"
#include "MIDI.h"

Sozai::Sozai() {
	x = 0;
	y = 0;
	exRate = 1.0;
	enableTurn = true;
	turnFlag = false;
	for (int i = 0; i < maxSozai; i++) {
		mySoundHandle[i] = -1;
		padSoundIndex[i] = 0;
		midiSoundIndex[i] = 0;
		isSoundPlay[i] = false;
	}
	for (int i = 0; i < maxPadSozai; i++) {
		triggerPad[i] = 0;
	}
	for (int i = 0; i < maxMidiSozai; i++) {
		triggerMidi[i] = 0;
	}
	validSoundNum = 0;
	validPadNum = 0;
	validMidiNum = 0;
	curSoundIndex = -1;
	curTriggerMidi = 0;
	enableMultiSound = false;
}

bool Sozai::update() {
	for (int i = 0; i < validMidiNum; i++) {
		int tmpMidiKey = triggerMidi[i];
		if (MIDI::getIns()->get(eMidi(tmpMidiKey)) == 0) {
			StopSoundMem(mySoundHandle[midiSoundIndex[i]]);
		}
	}
	return true;
}

void Sozai::draw() const {
	DrawRotaGraph(x, y, exRate, 0, myGrapghHandle, FALSE, (enableTurn && turnFlag));
}


/*
@brief �R���g���[���[�̃L�[�Ƒf�ނ̃y�A��ǉ�
*/
void Sozai::setTriggerPad(int padEnum, int soundIndexNum) {
	if (validPadNum < maxPadSozai) {
		triggerPad[validPadNum] = padEnum;
		midiSoundIndex[validPadNum] = soundIndexNum;
		validPadNum++;
	}
}

/*
@brief MIDI�̃L�[�Ƒf�ނ̃y�A��ǉ�
*/
void Sozai::setTriggerMidi(int midiEnum, int soundIndexNum) {
	if (validMidiNum < maxMidiSozai) {
		triggerMidi[validMidiNum] = midiEnum;
		midiSoundIndex[validMidiNum] = soundIndexNum;
		validMidiNum++;
	}
}


/*
@brief midi��pad�����肵�T�E���h���Ȃ炷 ����܂����R�[�h����Ȃ�����
*/
void Sozai::playSample(int sampleNum, bool isMidi) {
	int soundIndex;
	if (isMidi) {
		soundIndex = getMidiSoundIndex(sampleNum);
	}
	else {
		soundIndex = getPadSoundIndex(sampleNum);
	}
	turnFlag = (!turnFlag);	// ���]

	// ��������
	if (curSoundIndex != -1 && !enableMultiSound) {
		StopSoundMem(mySoundHandle[curSoundIndex]);
	}
	if (soundIndex >= 0 && soundIndex < maxSozai) {	// �z��͈͓̔����`�F�b�N
		if (mySoundHandle[soundIndex] != -1) {
			curSoundIndex = soundIndex;
			PlaySoundMem(mySoundHandle[curSoundIndex], DX_PLAYTYPE_BACK);
		}
	}
	// �f�����摜�̘A�ԂƂ��ď����ł���悤�Ɂ����ʂ��Ȃ�)
	SeekMovieToGraph(myGrapghHandle, 0);
	PlayMovieToGraph(myGrapghHandle);
}

void Sozai::setSampleMovie(const char* fileName) {
	myGrapghHandle = Image::getIns()->loadSamples(fileName);
}

/*
@brief �ǉ���������mySoundHandle�ɓ����Ă����ǉ�����Ƃ��͂��ꂪ�L�[�ԍ��ɂȂ�
*/
void Sozai::setSampleSound(const char* fileName) {
	if (validSoundNum < maxSozai) {
		mySoundHandle[validSoundNum] = Sound::getIns()->loadSamples(fileName);
		validSoundNum++;
	}
}
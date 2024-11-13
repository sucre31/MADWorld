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
}

bool Sozai::update() {
	if (MIDI::getIns()->get(eMidi(curTriggerMidi)) == 0) {
		if (curSoundIndex != -1) {
			StopSoundMem(mySoundHandle[curSoundIndex]);
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


void Sozai::playSample(int soundIndex) {
	turnFlag = (!turnFlag);	// ���]

	// ��������
	if (curSoundIndex != -1) {
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
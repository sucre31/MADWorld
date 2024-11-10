#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"

Sozai::Sozai() {
	x = 0;
	y = 0;
	enableTurn = false;
	turnFlag = false;
}

bool Sozai::update() {
	if (Pad::getIns()->get(ePad(triggerButton)) == 1) {
		playSample();
	}
	return true;
}

void Sozai::draw() const {
	DrawRotaGraph(x, y, 1.0, 0, myGrapghHandle, FALSE, enableTurn && turnFlag);
}

void Sozai::playSample() {
	turnFlag = !turnFlag;	// ���]

	// ��������
	StopSoundMem(mySoundHandle);
	PlaySoundMem(mySoundHandle, DX_PLAYTYPE_BACK);
	// �f������(�f���Ȃ���Ă����������邩���A�������͉f�����摜�̘A�ԂƂ��ď����ł���悤�Ɂ����ʂ��Ȃ�)
	SeekMovieToGraph(myGrapghHandle, 0);
	PlayMovieToGraph(myGrapghHandle);
}

void Sozai::setSampleMovie(const char* fileName) {
	myGrapghHandle = Image::getIns()->loadSamples(fileName);
}

void Sozai::setSampleSound(const char* fileName) {
	mySoundHandle = Sound::getIns()->loadSamples(fileName);
}
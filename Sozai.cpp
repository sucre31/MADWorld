#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"

Sozai::Sozai() {
	x = 0;
	y = 0;
	exRate = 1.0;
	enableTurn = true;
	turnFlag = false;
	triggerButton = 0;
	triggerMidi = 0;
	isValidButton = false;
	isValidMidi = false;
}

bool Sozai::update() {
	return true;
}

void Sozai::draw() const {
	DrawRotaGraph(x, y, exRate, 0, myGrapghHandle, FALSE, (enableTurn && turnFlag));
}

void Sozai::setTriggerButton(int padEnum) {
	triggerButton = padEnum;
	isValidButton = true;
}

void Sozai::setTriggerMidi(int midiEnum) {
	triggerMidi = midiEnum;
	isValidMidi = true;
}


void Sozai::playSample() {
	turnFlag = (!turnFlag);	// 反転

	// 音声処理
	StopSoundMem(mySoundHandle);
	PlaySoundMem(mySoundHandle, DX_PLAYTYPE_BACK);
	// 映像処理(映像ならっていう条件いるかも、もしくは映像も画像の連番として処理できるように←無駄がない)
	SeekMovieToGraph(myGrapghHandle, 0);
	PlayMovieToGraph(myGrapghHandle);
}

void Sozai::setSampleMovie(const char* fileName) {
	myGrapghHandle = Image::getIns()->loadSamples(fileName);
}

void Sozai::setSampleSound(const char* fileName) {
	mySoundHandle = Sound::getIns()->loadSamples(fileName);
}
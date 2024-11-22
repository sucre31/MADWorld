#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"
#include "MIDI.h"

Sozai::Sozai() :enablePadPlayStop(false) {
	x = 0;
	y = 0;
	transX = 198;
	transY = 0;
	exRate = 1.0;
	enableTurn = true;
	turnFlag = false;
	for (int i = 0; i < maxSozai; i++) {
		mySoundHandle[i] = -1;
		padSoundIndex[i] = 0;
		midiSoundIndex[i] = 0;
		isPadSoundPlay[i] = false;
		isMidiSoundPlay[i] = false;
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
	enableMultiSound = false;
	prevTime = GetNowCount();
	numOfPlayingSound = 0;
	isDrum = false;
}

bool Sozai::update() {
	for (int i = 0; i < validPadNum; i++) {
		int tmpPadKey = triggerPad[i];
		if (isPadSoundPlay[i] == true && Pad::getIns()->get(ePad(tmpPadKey)) == 0 && enablePadPlayStop) {
			StopSoundMem(mySoundHandle[padSoundIndex[i]]);
			numOfPlayingSound--;
			isPadSoundPlay[i] = false;
		}
	}
	for (int i = 0; i < validMidiNum; i++) {
		int tmpMidiKey = triggerMidi[i];
		if (isMidiSoundPlay[i] == true &&  MIDI::getIns()->get(eMidi(tmpMidiKey)) == 0) {
			if (isDrum == false) {
				StopSoundMem(mySoundHandle[midiSoundIndex[i]]);
			}
			numOfPlayingSound--;
			isMidiSoundPlay[i] = false;
		}
	}
	return true;
}

void Sozai::draw() const {
	if (enableMultiSound) {
		for (int i = 0; i < numOfPlayingSound; i++) {
			DrawRotaGraph(x + transX * (numOfPlayingSound - 1 - i), y + transY * (numOfPlayingSound - 1 - i), exRate, 0, myGrapghHandle, FALSE, (enableTurn && turnFlag));
		}
	}
	else {
		DrawRotaGraph(x, y, exRate, 0, myGrapghHandle, FALSE, (enableTurn && turnFlag));
	}
}


/*
@brief コントローラーのキーと素材のペアを追加
*/
void Sozai::setTriggerPad(int padEnum, int soundIndexNum) {
	if (validPadNum < maxPadSozai) {
		triggerPad[validPadNum] = padEnum;
		midiSoundIndex[validPadNum] = soundIndexNum;
		validPadNum++;
	}
}

/*
@brief MIDIのキーと素材のペアを追加
*/
void Sozai::setTriggerMidi(int midiEnum, int soundIndexNum) {
	if (validMidiNum < maxMidiSozai) {
		triggerMidi[validMidiNum] = midiEnum;
		midiSoundIndex[validMidiNum] = soundIndexNum;
		validMidiNum++;
	}
}


/*
@brief midiかpadか判定しサウンドをならす あんまいいコードじゃないかも
*/
void Sozai::playSample(int sampleNum, bool isMidi) {
	int soundIndex;
	if (isMidi) {
		soundIndex = getMidiSoundIndex(sampleNum);
	}
	else {
		soundIndex = getPadSoundIndex(sampleNum);
	}

	// 連続で音がなったとき(BPM基準で和音判定した方がいいかも)
	int tmpTime = GetNowCount();
	if (tmpTime - prevTime > 30) {
		turnFlag = (!turnFlag);	// 反転
	}
	prevTime = tmpTime;

	// 音声処理
	if (curSoundIndex != -1 && !enableMultiSound) {
		StopSoundMem(mySoundHandle[curSoundIndex]);
	}
	if (soundIndex >= 0 && soundIndex < maxSozai) {	// 配列の範囲内かチェック
		if (mySoundHandle[soundIndex] != -1) {
			curSoundIndex = soundIndex;
			PlaySoundMem(mySoundHandle[curSoundIndex], DX_PLAYTYPE_BACK);
			numOfPlayingSound++;
			if (isMidi == true) {
				isMidiSoundPlay[sampleNum] = true;
			}
			else {
				isPadSoundPlay[sampleNum] = true;
			}
		}
	}
	// 映像も画像の連番として処理できるように←無駄がない)
	SeekMovieToGraph(myGrapghHandle, 0);
	PlayMovieToGraph(myGrapghHandle);
}

void Sozai::setSampleMovie(const char* fileName) {
	myGrapghHandle = Image::getIns()->loadSamples(fileName);
}

/*
@brief 追加した順にmySoundHandleに入っていく追加するときはそれがキー番号になる
*/
void Sozai::setSampleSound(const char* fileName) {
	if (validSoundNum < maxSozai) {
		mySoundHandle[validSoundNum] = Sound::getIns()->loadSamples(fileName);
		validSoundNum++;
	}
}
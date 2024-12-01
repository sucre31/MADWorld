#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"
#include "MIDI.h"

Sozai::Sozai() :validGraphNum(0), enablePadPlayStop(false) {
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
	isMovie = false;
	playRate = 83;
	enableMultiGraph = false;
	enableMultiSprite = false;
}

bool Sozai::update() {
	if (timeForAnime.size() != 0) {
		for (int i = 0; i < timeForAnime.size(); i++) {
			curGraphNum[i] = (GetNowCount() - timeForAnime[i]) / playRate;
			if (curGraphNum[i] < 0) {
				curGraphNum[i] = 0;
			}
			if (curGraphNum[i] >= validGraphNum) {
				// �Đ��I��
				timeForAnime.erase(timeForAnime.begin() + i);
				curGraphNum.erase(curGraphNum.begin() + i);
				i--;
			}
		}
	}
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
	if (enableMultiGraph) {
		for (int i = 0; i < numOfPlayingSound; i++) {
			// �f����ǉ������s����1���G���������ĂȂ�
			DrawRotaGraph(x + transX * (numOfPlayingSound - 1 - i), y + transY * (numOfPlayingSound - 1 - i), exRate, 0, myGrapghHandle[0], TRUE, (enableTurn && turnFlag));
		}
	}
	else if (enableMultiSprite) {
		if (curGraphNum.size() != 0) {
			for (int i = 0; i < curGraphNum.size(); i++) {
				DrawRotaGraph(x, y, exRate, 0, myGrapghHandle[curGraphNum[i]], TRUE, (enableTurn && turnFlag));
			}
		}
		else {
			DrawRotaGraph(x, y, exRate, 0, myGrapghHandle[0], TRUE, (enableTurn && turnFlag));
		}
	}
	else {
		if (curGraphNum.size() != 0) {
			DrawRotaGraph(x, y, exRate, 0, myGrapghHandle[curGraphNum.back()], TRUE, (enableTurn && turnFlag));
		}
		else {
			DrawRotaGraph(x, y, exRate, 0, myGrapghHandle[0], TRUE, (enableTurn && turnFlag));
		}
	}
}

/*
@brief �R���g���[���[�̃L�[�Ƒf�ނ̃y�A��ǉ�
*/
void Sozai::setTriggerPad(int padEnum, int soundIndexNum) {
	if (validPadNum < maxPadSozai) {
		triggerPad[validPadNum] = padEnum;
		padSoundIndex[validPadNum] = soundIndexNum;
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

	// �A���ŉ����Ȃ����Ƃ�(BPM��Řa�����肵��������������)
	int tmpTime = GetNowCount();
	if (tmpTime - prevTime > 30) {
		turnFlag = (!turnFlag);	// ���]
	}
	prevTime = tmpTime;

	// ��������
	if (curSoundIndex != -1 && !enableMultiSound) {
		StopSoundMem(mySoundHandle[curSoundIndex]);
	}
	if (soundIndex >= 0 && soundIndex < maxSozai) {	// �z��͈͓̔����`�F�b�N
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

	// �f�����摜�̘A�ԂƂ��ď����ł���悤�Ɂ����ʂ��Ȃ�)
	if (isMovie) {
		SeekMovieToGraph(myGrapghHandle[0], 0);
		PlayMovieToGraph(myGrapghHandle[0]);
	}
	else {
		// �A��png���Đ����鏈��
		int startTime = GetNowCount() - playRate; // 1�t���[���i�߂�������v���C���[�g���Z���Ă邯�ǃo�O���邩��
		timeForAnime.push_back(startTime);
		curGraphNum.push_back(0);
	}
}

/*
@brief �f�ޔԍ��𒼐ڎw�肵�Ė炷
*/
void Sozai::playWithSoundIndex(int soundIndex) {
	// �A���ŉ����Ȃ����Ƃ�(BPM��Řa�����肵��������������)
	int tmpTime = GetNowCount();
	if (tmpTime - prevTime > 30) {
		turnFlag = (!turnFlag);	// ���]
	}
	prevTime = tmpTime;

	// ��������
	if (curSoundIndex != -1 && !enableMultiSound) {
		StopSoundMem(mySoundHandle[curSoundIndex]);
	}
	if (soundIndex >= 0 && soundIndex < maxSozai) {	// �z��͈͓̔����`�F�b�N
		if (mySoundHandle[soundIndex] != -1) {
			curSoundIndex = soundIndex;
			PlaySoundMem(mySoundHandle[curSoundIndex], DX_PLAYTYPE_BACK);
			numOfPlayingSound++;
			// playSample�ƈ���ĉ��Ԃ̉����Ȃ��Ă邩�Ƃ��͕ێ��ł��ĂȂ�
		}
	}
	if (isMovie) {
		SeekMovieToGraph(myGrapghHandle[0], 0);
		PlayMovieToGraph(myGrapghHandle[0]);
	}
	else {
		// �A��png���Đ����鏈��
		int startTime = GetNowCount() - playRate; // 1�t���[���i�߂�������v���C���[�g���Z���Ă邯�ǃo�O���邩��
		timeForAnime.push_back(startTime);
		curGraphNum.push_back(0);
	}
}

/*
@brief �A�ԉ摜��ǉ����A�j���[�V�����@1�f�ނɂ�1����z��
*/
void Sozai::addSprite(const char* fileName) {
	if (validGraphNum < maxSpriteNum) {
		myGrapghHandle[validGraphNum] = Image::getIns()->loadSamples(fileName);
		validGraphNum++;
	}
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
#include <Dxlib.h>
#include "SozaiManager.h"

SozaiManager::SozaiManager() {
	validSozaiNum = 0;
	for (int i = 0; i < limitOfSozai; i++) {
		SozaiLayerIndex[i] = i;
	}
}

/*
@brief �f�ނ̃C���X�^���X����
*/
void SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName) {
	if (validSozaiNum < limitOfSozai) {
		int sozaiNum = validSozaiNum;
		sozai[sozaiNum] = new Sozai();
		validSozaiNum++;
		sozai[sozaiNum]->setSampleSound(soundFileName);
		sozai[sozaiNum]->addSprite(imageFileName);
	}
}

/*
@brief �f�ނ̃C���X�^���X����
@param soundFileName �����t�@�C���̃p�X
@param imageFileName ����t�@�C���̃p�X
@param x �f�ނ�x�ʒu
@param y �f�ނ�y�ʒu
*/
void SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName, int x, int y) {
	if (validSozaiNum < limitOfSozai) {
		int sozaiNum = validSozaiNum;
		sozai[sozaiNum] = new Sozai();
		sozai[sozaiNum]->setSampleSound(soundFileName);
		sozai[sozaiNum]->addSprite(imageFileName);
		sozai[sozaiNum]->setPosX(x);
		sozai[sozaiNum]->setPosY(y);
		sozai[sozaiNum]->setMyId(validSozaiNum);
		validSozaiNum++;
	}
}

void SozaiManager::addSound(int sozaiNum, const char* soundFileName) {
	sozai[sozaiNum]->setSampleSound(soundFileName);
}

void SozaiManager::addSprites(int sozaiNum, const char* soundFileName) {
	sozai[sozaiNum]->addSprite(soundFileName);
}

/*
@brief �f�ނ𒼐ڂȂ炷
*/
void SozaiManager::playSozai(int sozaiNum, int soundIndex) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->playWithSoundIndex(soundIndex);
	}
}

/*
@brief �f�ޔԍ����󂯎��L�[���o�C���h
*/
void SozaiManager::setSozaiKey(int sozaiNum, int padNum, int soundIndex) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerPad(padNum, soundIndex);
	}
}

/*
@brief �f�ޔԍ����󂯎��MIDI�L�[���o�C���h
*/
void SozaiManager::setSozaiMidiKey(int sozaiNum, int midiNum, int soundIndex) {
	// �����L�[�o�C���h�ł���悤�ɂ������@�����ύX�݂̂Ȃ�
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerMidi(midiNum, soundIndex);
	}
}

/*
@brief �f�ޔԍ����󂯎��{���ݒ�
*/
void SozaiManager::setSozaiEx(int sozaiNum, double val) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setExRate(val);
	}
}

/*
@brief �f�ޔԍ����󂯎��{���ݒ�
*/
void SozaiManager::setSozaiPos(int sozaiNum, int valX, int valY) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setPosX(valX);
		sozai[sozaiNum]->setPosY(valY);
	}
}

/*
@brief ���������Ȃ炷���Ƃ������邩
*/
void SozaiManager::setMultiSound(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setMultiSound(flag);
	}
}

/*
@brief �摜�������o�Ă��� YTPMV�p
*/
void SozaiManager::setMultiGraph(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setMultiGraph(flag);
	}
}

/*
@brief �h�����p��midi�̃I�t���𖳎�����
*/
void SozaiManager::setDrumFlag(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setIsDrum(flag);
	}
}

/*
@brief �h�����p��midi�̃I�t���𖳎�����
*/
void SozaiManager::setPadReleaseStop(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setPadReleaseStop(flag);
	}
}

/*
@brief ���悩�摜�̘A�Ԃ��w��
*/
void SozaiManager::setMovieFlag(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setUseMovie(flag);
	}
}

void SozaiManager::setReverseFlag(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setUseTurn(flag);
	}
}


void SozaiManager::changeTopLayer(int sozaiId) {
	// �蔲�� �����ƃ\�[�g�����悤�ɂȂ���
	SozaiLayerIndex[0] = sozaiId;
}

void SozaiManager::changePos(int sozaiNum, double valX, double valY) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setPosX(sozai[sozaiNum]->getPosX() + valX);
		sozai[sozaiNum]->setPosY(sozai[sozaiNum]->getPosY() + valY);
	}
}

bool SozaiManager::update() {
	for (int i = 0; i < validSozaiNum; i++ ) {
		for (int j = 0; j < sozai[i]->getValidPadNum(); j++) {
			if (Pad::getIns()->get(ePad(sozai[i]->getTriggerPad(j))) == 1) {
				sozai[i]->playSample(j, false);
				changeTopLayer(i);
			}
		}
		for (int j = 0; j < sozai[i]->getValidMidiNum(); j++) {
			if (MIDI::getIns()->get(eMidi(sozai[i]->getTriggerMidi(j))) == 1) {
				sozai[i]->playSample(j, true);
				changeTopLayer(i);
			}
		}
		sozai[i]->update();
	}
	return true;
}

void SozaiManager::draw() const {
	for (int i = 0; i < validSozaiNum; i++) {
		sozai[i]->draw();
	}
	// �蔲��
	sozai[SozaiLayerIndex[0]]->draw();
}

void SozaiManager::drawSozai(int sozaiNum) const {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->draw();
	}
}

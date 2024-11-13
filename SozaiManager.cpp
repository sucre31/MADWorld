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
		sozai[sozaiNum]->setSampleMovie(imageFileName);
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
		sozai[sozaiNum]->setSampleMovie(imageFileName);
		sozai[sozaiNum]->setPosX(x);
		sozai[sozaiNum]->setPosY(y);
		sozai[sozaiNum]->setMyId(validSozaiNum);
		validSozaiNum++;
	}
}

/*
@brief �f�ޔԍ����󂯎��L�[���o�C���h
*/
void SozaiManager::setSozaiKey(int sozaiNum, int padNum) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerButton(padNum);
	}
}

/*
@brief �f�ޔԍ����󂯎��MIDI�L�[���o�C���h
*/
void SozaiManager::setSozaiMidiKey(int sozaiNum, int midiNum) {
	// �����L�[�o�C���h�ł���悤�ɂ������@�����ύX�݂̂Ȃ�
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerMidi(midiNum);
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



void SozaiManager::changeTopLayer(int sozaiId) {
	// �蔲�� �����ƃ\�[�g�����悤�ɂȂ���
	SozaiLayerIndex[0] = sozaiId;
}

bool SozaiManager::update() {
	for (int i = 0; i < validSozaiNum; i++ ) {
		if (sozai[i]->isVaildButtonInput() && Pad::getIns()->get(ePad(sozai[i]->getTriggerButton())) == 1) {
			sozai[i]->playSample();
			changeTopLayer(i);
		}
		if (sozai[i]->isVaildMidiInput() &&  MIDI::getIns()->get(eMidi(sozai[i]->getTriggerMidi())) == 1) {
			sozai[i]->playSample();
			changeTopLayer(i);
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

#include <Dxlib.h>
#include "SozaiManager.h"

SozaiManager::SozaiManager() {
	validSozaiNum = 0;
	for (int i = 0; i < limitOfSozai; i++) {
		SozaiLayerIndex[i] = i;
	}
}

/*
@brief 素材のインスタンス生成
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
@brief 素材のインスタンス生成
@param soundFileName 音声ファイルのパス
@param imageFileName 動画ファイルのパス
@param x 素材のx位置
@param y 素材のy位置
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

void SozaiManager::addSound(int sozaiNum, const char* soundFileName) {
	sozai[sozaiNum]->setSampleSound(soundFileName);
}

/*
@brief 素材番号を受け取りキーをバインド
*/
void SozaiManager::setSozaiKey(int sozaiNum, int padNum, int soundIndex) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerPad(padNum, soundIndex);
	}
}

/*
@brief 素材番号を受け取りMIDIキーをバインド
*/
void SozaiManager::setSozaiMidiKey(int sozaiNum, int midiNum, int soundIndex) {
	// 複数キーバインドできるようにしたい　音程変更のみなら
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setTriggerMidi(midiNum, soundIndex);
	}
}

/*
@brief 素材番号を受け取り倍率設定
*/
void SozaiManager::setSozaiEx(int sozaiNum, double val) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setExRate(val);
	}
}

/*
@brief 素材番号を受け取り倍率設定
*/
void SozaiManager::setSozaiPos(int sozaiNum, int valX, int valY) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setPosX(valX);
		sozai[sozaiNum]->setPosY(valY);
	}
}



void SozaiManager::changeTopLayer(int sozaiId) {
	// 手抜き ちゃんとソートされるようになおす
	SozaiLayerIndex[0] = sozaiId;
}

bool SozaiManager::update() {
	for (int i = 0; i < validSozaiNum; i++ ) {
		for (int j = 0; j < sozai[i]->getValidPadNum(); j++) {
			if (Pad::getIns()->get(ePad(sozai[i]->getTriggerPad(j))) == 1) {
				sozai[i]->playSample(sozai[i]->getPadSoundIndex(j));
				changeTopLayer(i);
			}
		}
		for (int j = 0; j < sozai[i]->getValidMidiNum(); j++) {
			if (MIDI::getIns()->get(eMidi(sozai[i]->getTriggerMidi(j))) == 1) {
				sozai[i]->playSample(sozai[i]->getMidiSoundIndex(j));
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
	// 手抜き
	sozai[SozaiLayerIndex[0]]->draw();
}

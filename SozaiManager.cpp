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
		sozai[sozaiNum]->addSprite(imageFileName);
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
@brief 素材を直接ならす
*/
void SozaiManager::playSozai(int sozaiNum, int soundIndex) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->playWithSoundIndex(soundIndex);
	}
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

/*
@brief 複数音をならすことを許可するか
*/
void SozaiManager::setMultiSound(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setMultiSound(flag);
	}
}

/*
@brief 画像が複数出てくる YTPMV用
*/
void SozaiManager::setMultiGraph(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setMultiGraph(flag);
	}
}

/*
@brief ドラム用にmidiのオフ情報を無視する
*/
void SozaiManager::setDrumFlag(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setIsDrum(flag);
	}
}

/*
@brief ドラム用にmidiのオフ情報を無視する
*/
void SozaiManager::setPadReleaseStop(int sozaiNum, bool flag) {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->setPadReleaseStop(flag);
	}
}

/*
@brief 動画か画像の連番か指定
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
	// 手抜き ちゃんとソートされるようになおす
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
	// 手抜き
	sozai[SozaiLayerIndex[0]]->draw();
}

void SozaiManager::drawSozai(int sozaiNum) const {
	if (sozaiNum < validSozaiNum) {
		sozai[sozaiNum]->draw();
	}
}

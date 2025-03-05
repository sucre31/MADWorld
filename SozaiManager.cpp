#include <Dxlib.h>
#include "SozaiManager.h"

SozaiManager::SozaiManager() {
}

/*
@brief 素材のインスタンス生成
*/
void SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName) {
	sozai.push_back(new Sozai());
	sozai.back()->setSampleSound(soundFileName);
	sozai.back()->addSprite(imageFileName);
	sozai.back()->setMyId(sozai.size() - 1);
	SozaiLayerIndex.push_back(sozai.size() - 1);
}

/*
@brief 素材のインスタンス生成
@param soundFileName 音声ファイルのパス
@param imageFileName 動画ファイルのパス
@param x 素材のx位置
@param y 素材のy位置
*/
void SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName, int x, int y) {
	sozai.push_back(new Sozai());
	sozai.back()->setSampleSound(soundFileName);
	sozai.back()->addSprite(imageFileName);
	sozai.back()->setPosX(x);
	sozai.back()->setPosY(y);
	sozai.back()->setMyId(sozai.size() - 1);
	SozaiLayerIndex.push_back(sozai.size() - 1);
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
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->playWithSoundIndex(soundIndex);
		changeTopLayer(sozai[sozaiNum]->getMyId());
	}
}

/*
@brief 素材番号を受け取りキーをバインド
*/
void SozaiManager::setSozaiKey(int sozaiNum, int padNum, int soundIndex) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setTriggerPad(padNum, soundIndex);
	}
}

void SozaiManager::resetSozaiKey(int sozaiNum) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->resetTriggerPad();
	}
}

/*
@brief 素材番号を受け取りMIDIキーをバインド
*/
void SozaiManager::setSozaiMidiKey(int sozaiNum, int midiNum, int soundIndex) {
	// 複数キーバインドできるようにしたい　音程変更のみなら
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setTriggerMidi(midiNum, soundIndex);
	}
}

/*
@brief 素材番号を受け取り倍率設定
*/
void SozaiManager::setSozaiEx(int sozaiNum, double val) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setExRate(val);
	}
}

/*
@brief 素材番号を受け取り位置設定
*/
void SozaiManager::setSozaiPos(int sozaiNum, int valX, int valY) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setPosX(valX);
		sozai[sozaiNum]->setPosY(valY);
	}
}

/*
@brief 複数音をならすことを許可するか
*/
void SozaiManager::setMultiSound(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setMultiSound(flag);
	}
}

/*
@brief 画像が複数出てくる YTPMV用
*/
void SozaiManager::setMultiGraph(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setMultiGraph(flag);
	}
}

/*
@brief ドラム用にmidiのオフ情報を無視する
*/
void SozaiManager::setDrumFlag(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setIsDrum(flag);
	}
}

/*
@brief ドラム用にmidiのオフ情報を無視する
*/
void SozaiManager::setPadReleaseStop(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setPadReleaseStop(flag);
	}
}

/*
@brief 動画か画像の連番か指定
*/
void SozaiManager::setMovieFlag(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setUseMovie(flag);
	}
}

void SozaiManager::setReverseFlag(int sozaiNum, bool flag) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setUseTurn(flag);
	}
}

/*
@brief 素材の再生速度変更
*/
void SozaiManager::setPlayRate(int sozaiNum, int rateVal) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setPlayRate(rateVal);
	}
}


void SozaiManager::changeTopLayer(int sozaiId) {
	// 手抜き ちゃんとソートされるようになおす
	if (SozaiLayerIndex.size() > 0) {
		SozaiLayerIndex[0] = sozaiId;
	}
}

void SozaiManager::changePos(int sozaiNum, double valX, double valY) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setPosX(sozai[sozaiNum]->getPosX() + valX);
		sozai[sozaiNum]->setPosY(sozai[sozaiNum]->getPosY() + valY);
	}
}

bool SozaiManager::update() {
	for (int i = 0; i < sozai.size(); i++ ) {
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
	for (int i = 0; i < sozai.size(); i++) {
		sozai[i]->draw();
	}
	// 手抜き
	if (SozaiLayerIndex.size() > 0) {
		sozai[SozaiLayerIndex[0]]->draw();
	}
}

void SozaiManager::drawSozai(int sozaiNum) const {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->draw();
	}
}

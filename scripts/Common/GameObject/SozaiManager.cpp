# include <map>
#include <Dxlib.h>
#include "SozaiManager.h"

SozaiManager::SozaiManager() {
}

/*
@brief 素材のインスタンス生成
*/
int SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName) {
	sozai.push_back(new Sozai());
	sozai.back()->setSampleSound(soundFileName);
	sozai.back()->addSprite(imageFileName);
	sozai.back()->setMyId(sozai.size() - 1);
	SozaiLayerIndex.push_back(sozai.size() - 1);
	return static_cast<int>(sozai.size()) - 1;
}

/*
@brief 素材のインスタンス生成
@param soundFileName 音声ファイルのパス
@param imageFileName 動画ファイルのパス
@param x 素材のx位置
@param y 素材のy位置
*/
int SozaiManager::makeSozai(const char* soundFileName, const char* imageFileName, int x, int y) {
	sozai.push_back(new Sozai());
	sozai.back()->setSampleSound(soundFileName);
	sozai.back()->addSprite(imageFileName);
	sozai.back()->setPosX(x);
	sozai.back()->setPosY(y);
	sozai.back()->setMyId(sozai.size() - 1);
	SozaiLayerIndex.push_back(sozai.size() - 1);
	return static_cast<int>(sozai.size()) - 1;
}

void SozaiManager::addSound(int sozaiNum, const char* soundFileName) {
	sozai[sozaiNum]->setSampleSound(soundFileName);
}

void SozaiManager::addSprite(int sozaiNum, const char* spriteFileName) {
	sozai[sozaiNum]->addSprite(spriteFileName);
}

void SozaiManager::addSprite(int sozaiNum, int soundIndex, const char* fileName)
{
	sozai[sozaiNum]->addSprite(soundIndex, fileName);
}

void SozaiManager::setSozaiLayer(int sozaiNum, int layer)
{
	if (sozaiNum < sozai.size())
	{
		sozai[sozaiNum]->setLayer(layer);
	}
}

/*
@brief 素材を直接ならす
*/
void SozaiManager::playSozai(int sozaiNum, int soundIndex) {
	if (sozaiNum >= sozai.size()) return;

	int groupId = sozai[sozaiNum]->getGroupId();

	// 同じグループの他の音を停止
	if (groupId != -1) {
		for (int i = 0; i < sozai.size(); i++) {
			if (i != sozaiNum && sozai[i]->getGroupId() == groupId) {
				sozai[i]->stopSound();
			}
		}
	}

	sozai[sozaiNum]->playWithSoundIndex(soundIndex);
	changeTopLayer(sozai[sozaiNum]->getMyId());
}

/*
@brief 素材を直接止める
*/
void SozaiManager::stopSozai(int sozaiNum) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->stopSound();
	}
}

/*
@brief 素材番号を受け取りキーをバインド
@param sozaiNum 登録済みの素材番号
@param padNum コントローラのキー番号
@param soundIndex 再生する音のインデックス
*/
void SozaiManager::setSozaiKey(int sozaiNum, int padNum, int soundIndex) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setTriggerPad(padNum, soundIndex);

		padToSozai[(ePad)padNum].push_back(sozaiNum);
	}
}

void SozaiManager::resetSozaiKey(int sozaiNum) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->resetTriggerPad();
	}
}

void SozaiManager::resetMidiKey(int sozaiNum) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->resetTriggerMidi();
	}
}


/*
@brief 素材番号を受け取りMIDIキーをバインド
*/
void SozaiManager::setSozaiMidiKey(int sozaiNum, int midiNum, int soundIndex, int channel)
{
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setTriggerMidi(midiNum, soundIndex, channel);
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


void SozaiManager::changeTopLayer(int sozaiId)
{
	// すでに登録されている位置を探す
	auto it = std::find(SozaiLayerIndex.begin(), SozaiLayerIndex.end(), sozaiId);

	// 見つかったら一度削除
	if (it != SozaiLayerIndex.end()) {
		SozaiLayerIndex.erase(it);
	}

	// 一番上（最後）に追加
	SozaiLayerIndex.push_back(sozaiId);
}

void SozaiManager::changePos(int sozaiNum, double valX, double valY) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setPosX(sozai[sozaiNum]->getPosX() + valX);
		sozai[sozaiNum]->setPosY(sozai[sozaiNum]->getPosY() + valY);
	}
}

void SozaiManager::setGroupId(int sozaiNum, int groupId) {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->setGroupId(groupId);
	}
}

int SozaiManager::getSoundCount(int sozaiNum) const {
	if (sozaiNum < sozai.size()) {
		return sozai[sozaiNum]->getSoundCount();
	}
	return 0;
}


bool SozaiManager::update() {
	for (int i = 0; i < sozai.size(); i++) {
		// コントローラの入力確認
		for (int p = 0; p < (int)ePad::MAX; p++) {
			if (Pad::getIns()->get((ePad)p) != 1) continue; // キー入力無し
			auto it = padToSozai.find((ePad)p); // 素材番号
			if (it == padToSozai.end()) continue;
			for (int i : it->second) {
				for (int j = 0; j < sozai[i]->getValidPadNum(); j++) {
					if (sozai[i]->getTriggerPad(j) != p) continue;
					int groupId = sozai[i]->getGroupId();
					if (groupId != -1) {
						for (int k = 0; k < sozai.size(); k++) {
							if (k != i && sozai[k]->getGroupId() == groupId) {
								sozai[k]->stopSound();
							}
						}
					}
					sozai[i]->playSample(j, false);
					changeTopLayer(i);
				}
			}
		}

		// Midiの入力確認
		for (int j = 0; j < sozai[i]->getValidMidiNum(); j++) {
			int note = sozai[i]->getTriggerMidiNote(j);
			int channel = sozai[i]->getTriggerMidiChannel(j);

			if (MIDI::getIns()->isTrigger(note, channel))
			{
				int groupId = sozai[i]->getGroupId();
				if (groupId != -1) {
					for (int k = 0; k < sozai.size(); k++) {
						if (k != i && sozai[k]->getGroupId() == groupId) {
							sozai[k]->stopSound();
						}
					}
				}

				sozai[i]->playSample(j, true);
				changeTopLayer(i);
			}
		}
		sozai[i]->update();
	}
	return true;
}

void SozaiManager::draw() const
{
	std::map<int, std::vector<int>> layerMap;

	for (int id : SozaiLayerIndex)
	{
		int layer = sozai[id]->getLayer();
		layerMap[layer].push_back(id);
	}

	for (auto& layer : layerMap)
	{
		for (int id : layer.second)
		{
			sozai[id]->draw();
		}
	}
}

void SozaiManager::drawSozai(int sozaiNum) const {
	if (sozaiNum < sozai.size()) {
		sozai[sozaiNum]->draw();
	}
}

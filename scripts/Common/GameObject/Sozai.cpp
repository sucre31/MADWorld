#include <Dxlib.h>
#include "Common/Image.h"
#include "Sozai.h"
#include "Common/Sound.h"
#include "System/Pad.h"
#include "System/MIDI.h"

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
		midiSoundIndex[i] = 0;
		isPadSoundPlay[i] = false;
		isMidiSoundPlay[i] = false;
	}
	for (int i = 0; i < maxMidiSozai; i++) {
		triggerMidiNote[i] = 0;
	}
	validSoundNum = 0;
	validMidiNum = 0;
	curSoundIndex = -1;
	enableMultiSound = false;
	prevTime = GetNowCount();
	numOfPlayingSound = 0;
	isDrum = false;
	playRate = 88;
	enableMultiGraph = false;
	enableMultiSprite = false;
}

Sozai::~Sozai() {
	// 溜め込んだ画像ハンドルをすべてDXライブラリから削除
	for (int handle : myGrapghHandle) {
		DeleteGraph(handle);
	}
	myGrapghHandle.clear();
}

bool Sozai::update() {
	if (timeForAnime.size() != 0) {
		for (int i = 0; i < (int)timeForAnime.size(); i++) {
			// 現在のフレームを計算
			int frame = (GetNowCount() - timeForAnime[i]) / playRate;

			if (frame < 0) frame = 0;

			// 最終フレームを超えた場合
			if (frame >= (int)myGrapghHandle.size()) {
				curGraphNum[i] = (int)myGrapghHandle.size() - 1; // 最終フレームで固定
				// timeForAnime.erase(...) はしない。ただし何度も計算しない工夫が必要ならフラグ管理
				// 今回はシンプルに、eraseしないことで描画側が curGraphNum を使い続けるようにします
			}
			else {
				curGraphNum[i] = frame;
			}
		}
	}
	for (int i = 0; i < triggerPad.size(); i++) {
		int tmpPadKey = triggerPad[i];
		if (isPadSoundPlay[i] == true && Pad::getIns()->get(ePad(tmpPadKey)) == 0 && enablePadPlayStop) {
			StopSoundMem(mySoundHandle[padSoundIndex[i]]);
			numOfPlayingSound--;
			isPadSoundPlay[i] = false;
		}
	}
	for (int i = 0; i < validMidiNum; i++) {
		int note = triggerMidiNote[i];
		int channel = triggerMidiChannel[i];

		if (isMidiSoundPlay[i] == true &&
			MIDI::getIns()->get(note, channel) == 0) {

			if (!isDrum) {
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
			// 映像を追加した都合で1枚絵しかだせてない
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
@brief コントローラーのキーと素材のペアを追加
*/
void Sozai::setTriggerPad(int padEnum, int soundIndexNum) {
	triggerPad.push_back(padEnum);
	padSoundIndex.push_back(soundIndexNum);
}

/*
@brief コントローラーのキーと素材のペアを完全に削除
*/
void Sozai::resetTriggerPad() {
	triggerPad.clear();
	padSoundIndex.clear();
}

/*
@brief MIDIのキーと素材のペアを追加
*/
void Sozai::setTriggerMidi(int midiEnum, int soundIndexNum) {
	if (validMidiNum < maxMidiSozai) {
		triggerMidiNote[validMidiNum] = midiEnum;
		triggerMidiChannel[validMidiNum] = 0;   // デフォルトはch0
		midiSoundIndex[validMidiNum] = soundIndexNum;
		validMidiNum++;
	}
}

void Sozai::setTriggerMidi(int midiNote, int soundIndexNum, int channel)
{
	if (validMidiNum < maxMidiSozai) {
		triggerMidiNote[validMidiNum] = midiNote;
		triggerMidiChannel[validMidiNum] = channel;
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
	int startTime = GetNowCount();
	timeForAnime.push_back(startTime);
	curGraphNum.push_back(0);
}

/*
@brief 素材番号を直接指定して鳴らす
*/
void Sozai::playWithSoundIndex(int soundIndex) {
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
			// playSampleと違って何番の音がなってるかとかは保持できてない
		}
	}
	int startTime = GetNowCount();
	timeForAnime.push_back(startTime);
	curGraphNum.push_back(0);
}

/*
@brief 再生停止
*/
void Sozai::stopSound() {
	if (curSoundIndex != -1 && !enableMultiSound) {
		StopSoundMem(mySoundHandle[curSoundIndex]);
	}
}

/*
@brief 連番画像を追加しアニメーション　1素材につき1動画想定
*/
void Sozai::addSprite(const char* fileName) {
	std::string path(fileName);
	std::string ext;
	size_t dotPos = path.find_last_of(".");
	if (dotPos != std::string::npos) {
		ext = path.substr(dotPos + 1);
		for (auto& c : ext) c = tolower(c);
	}

	if (ext == "mp4" || ext == "avi") {
		// 動画をロードしてハンドル配列をマージする
		MovieData movie = MovieImageWrapper::load(path);
		myGrapghHandle.insert(myGrapghHandle.end(), movie.handles.begin(), movie.handles.end());
		if (!movie.handles.empty()) {
			this->playRate = movie.msPerFrame;
		}
	}
	else {
		// 通常画像
		myGrapghHandle.push_back(Image::getIns()->loadSamples(fileName));
	}
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
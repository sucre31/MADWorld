#include <DxLib.h>
#include "Common/Sound.h"
#include "Common/Image.h"
#include "System/Define.h"
#include "System/Keyboard.h"
#include "System/Pad.h"
#include "System/MIDI.h"
#include "SceneLoveSong.h"


SceneLoveSong::SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	isMusicPlay(false),
	movieTurnFlag(false),
	musicIndex(0),
	strIndex(1),
	stringRevive("＊")
{
	// フォント設定
	initializeFont();

	// 音楽とサンプルのロード
	initializeMusic();

	// 画像とMIDIのロード
	initializeResources();
}

void SceneLoveSong::initializeFont() {
	ChangeFont("DragonQuestFC");
	SetFontSpace(3);
	SetFontSize(48);
	SetFontThickness(1);
}

void SceneLoveSong::initializeMusic() {
	// MusicManagerを使用して音楽をロード
	musicManager.LoadMusic("LoveSong", "Assets/Sounds/LoveSong/LoveSongDQ2.wav");
	musicManager.LoadMusic("DrumLoop", "Assets/Sounds/LoveSong/drumLoop.wav");
}

void SceneLoveSong::initializeResources() {
	loadLoveSongSamples();
	backGroundHandle = Image::getIns()->loadSamples("Assets/sprites/images/LoveSongBackBlack.png");
	// MIDIファイルをオープン
	MIDI::getIns()->openMidi(0, 0);
}

void SceneLoveSong::loadLoveSongSamples() {
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample0.wav", "Assets/sprites/movie/LoveMovieSmall0.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample1.wav", "Assets/sprites/movie/LoveMovieSmall1.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample2.wav", "Assets/sprites/movie/LoveMovieSmall2.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample3.wav", "Assets/sprites/movie/LoveMovieSmall3.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample4.wav", "Assets/sprites/movie/LoveMovieSmall4.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample5.wav", "Assets/sprites/movie/LoveMovieSmall5.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample6.wav", "Assets/sprites/movie/LoveMovieSmall6.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample7.wav", "Assets/sprites/movie/LoveMovieSmall7.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample0.wav", "Assets/sprites/movie/Large/LoveMovieLarge0.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample1.wav", "Assets/sprites/movie/Large/LoveMovieLarge1.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample2.wav", "Assets/sprites/movie/Large/LoveMovieLarge2.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample3.wav", "Assets/sprites/movie/Large/LoveMovieLarge3.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample4.wav", "Assets/sprites/movie/Large/LoveMovieLarge4.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample5.wav", "Assets/sprites/movie/Large/LoveMovieLarge5.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample6.wav", "Assets/sprites/movie/Large/LoveMovieLarge6.avi");
	sozaiManager.makeSozai("Assets/Sounds/LoveSong/LoveSample7.wav", "Assets/sprites/movie/Large/LoveMovieLarge7.avi");

	sozaiManager.setSozaiKey(0, ePad::down, 0);
	sozaiManager.setSozaiKey(1, ePad::left, 0);
	sozaiManager.setSozaiKey(2, ePad::up, 0);
	sozaiManager.setSozaiKey(3, ePad::right, 0);
	sozaiManager.setSozaiKey(4, ePad::Y, 0);
	sozaiManager.setSozaiKey(5, ePad::B, 0);
	sozaiManager.setSozaiKey(6, ePad::A, 0);
	sozaiManager.setSozaiKey(7, ePad::X, 0);

	for (int i = 0; i < sozaiNum; i++) {
		sozaiManager.setSozaiEx(i, 1);
		sozaiManager.setMovieFlag(i, true);
		sozaiManager.setGroupId(i, 1);	// id1グループに素材設定
	}

	setSozaiPosNoBGM();
}

void SceneLoveSong::setSozaiPosNoBGM() {
	sozaiManager.resetSozaiKey(0);
	sozaiManager.resetSozaiKey(1);
	sozaiManager.resetSozaiKey(2);
	sozaiManager.resetSozaiKey(3);
	sozaiManager.resetSozaiKey(4);
	sozaiManager.resetSozaiKey(5);
	sozaiManager.resetSozaiKey(6);
	sozaiManager.resetSozaiKey(7);
	sozaiManager.setSozaiKey(8, ePad::down, 0);
	sozaiManager.setSozaiKey(9, ePad::left, 0);
	sozaiManager.setSozaiKey(10, ePad::up, 0);
	sozaiManager.setSozaiKey(11, ePad::right, 0);
	sozaiManager.setSozaiKey(12, ePad::Y, 0);
	sozaiManager.setSozaiKey(13, ePad::B, 0);
	sozaiManager.setSozaiKey(14, ePad::A, 0);
	sozaiManager.setSozaiKey(15, ePad::X, 0);
	for (int i = 0; i < sozaiNum; i++) {
		if (i >= sozaiNum / 2) {
			sozaiManager.setSozaiPos(i, 640, 360);
		}
		else {
			sozaiManager.setSozaiPos(i, -640, 360);
		}
	}
}

void SceneLoveSong::setSozaiPosPlay() {
	sozaiManager.setSozaiKey(0, ePad::down, 0);
	sozaiManager.setSozaiKey(1, ePad::left, 0);
	sozaiManager.setSozaiKey(2, ePad::up, 0);
	sozaiManager.setSozaiKey(3, ePad::right, 0);
	sozaiManager.setSozaiKey(4, ePad::Y, 0);
	sozaiManager.setSozaiKey(5, ePad::B, 0);
	sozaiManager.setSozaiKey(6, ePad::A, 0);
	sozaiManager.setSozaiKey(7, ePad::X, 0);
	sozaiManager.resetSozaiKey(8);
	sozaiManager.resetSozaiKey(9);
	sozaiManager.resetSozaiKey(10);
	sozaiManager.resetSozaiKey(11);
	sozaiManager.resetSozaiKey(12);
	sozaiManager.resetSozaiKey(13);
	sozaiManager.resetSozaiKey(14);
	sozaiManager.resetSozaiKey(15);
	for (int i = 0; i < sozaiNum; i++) {
		if (i >= sozaiNum / 2) {
			// 非表示
			sozaiManager.setSozaiPos(i, -640, 0);
		}
		else {
			sozaiManager.setSozaiPos(i, 400 + 240, 400 + 135);
		}
	}
}


void SceneLoveSong::update()
{
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::L) == 1) {
		// 音楽再生
		if (!isMusicPlay) {
			musicManager.Play("LoveSong", true);  // Play using MusicManager
			musicIndex = 0;
			isMusicPlay = true;
			setSozaiPosPlay();
			resetString();
		}
		else if (musicIndex == 0) {
			musicManager.Stop();  // Stop using MusicManager
			isMusicPlay = false;
			setSozaiPosNoBGM();
		}
		else {
			musicManager.Stop();  // Stop using MusicManager
			musicManager.Play("LoveSong", true);  // Play again using MusicManager
			musicIndex = 0;
			isMusicPlay = true;
		}
	}
	if (Pad::getIns()->get(ePad::R) == 1) {
		// 音楽再生
		if (!isMusicPlay) {
			musicManager.Play("DrumLoop", true);  // Play using MusicManager
			musicIndex = 1;
			isMusicPlay = true;
			setSozaiPosPlay();
		}
		else if (musicIndex == 1) {
			musicManager.Stop();  // Stop using MusicManager
			isMusicPlay = false;
			setSozaiPosNoBGM();
		}
		else {
			musicManager.Stop();  // Stop using MusicManager
			musicManager.Play("DrumLoop", true);  // Play again using MusicManager
			musicIndex = 1;
			isMusicPlay = true;
			setSozaiPosPlay();
		}
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		addReviveChar("ぱ");
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		addReviveChar("わ");
		//addReviveChar("い");
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		addReviveChar("ち");
		addReviveChar("ゆ");
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		addReviveChar("き");
		addReviveChar("ゆ");
		//addReviveChar("ん");
	}
	if (Pad::getIns()->get(ePad::Y) == 1) {
		addReviveChar("は");
		//addReviveChar("あ");
		///addReviveChar("ん");
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		addReviveChar("お");
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		addReviveChar("が");
	}
	if (Pad::getIns()->get(ePad::X) == 1) {
		addReviveChar("し");
		addReviveChar("や");
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		MIDI::getIns()->closeMidi(0);
		clsDx();
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(Sound::getIns()->getLoveSong()[musicIndex]);
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

/*
@brief ワイド文字（ひらがな）を受け取って末尾の文字に追加
*/
void SceneLoveSong::addReviveChar(std::string mes) {
	if (strIndex <= strSize - 1) {
		// ひらがななので2byte分消す 不具合起きる可能性あるかも
		// あと一文字(2byte)しか引数に取らないようにすべき
		if (strIndex % 14 == 3 || strIndex % 14 == 8) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "　　＊";
			strIndex+=3;
		}
		else if (strIndex == 70) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "　＊";
			strIndex += 2;
		}
		else if (strIndex == 74) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes;
			strIndex += 2;
		}
		else {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "＊";
			strIndex++;
		}
	}
	else {
		stringRevive.erase(0);
		strIndex = 1;
		stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes +"＊";
		strIndex++;
	}
}

void SceneLoveSong::resetString() {
	stringRevive.erase(0);
	strIndex = 1;
	stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + "＊";
}


void SceneLoveSong::draw() const
{
	musicManager.draw();
	if (isMusicPlay) {
		DrawGraph(0, 0, backGroundHandle, FALSE);
		DrawString(400, 30, "ふっかつのじゅもんを いれてください", GetColor(255, 255, 255));

		// じゅもん描画
		int strLength = strIndex * 2;
		for (int i = 0; i < 5; i++) {
			if (i == 4) {
				if (strLength > i * 28) {
					DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 36).c_str(), GetColor(255, 255, 255));
					if (strLength < (i + 1) * 28) {
						// 文字が入っている最後の行
						break;
					}
				}
			}
			else {
				if (strLength > i * 28) {
					DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 28).c_str(), GetColor(255, 255, 255));
					if (strLength < (i + 1) * 28) {
						// 文字が入っている最後の行
						break;
					}
				}
			}
		}
	}
	sozaiManager.draw();
}
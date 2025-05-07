#include <DxLib.h>
#include "Common/Sound.h"
#include "Common/Image.h"
#include "System/Pad.h"
#include "SceneSeikanHikou.h"


SceneSeikanHikou::SceneSeikanHikou(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	sampleSetNum(0),
	enablePause(false),
	noteManager(140, 4, &sozaiManager)
	{
	// 素材の読み込み
	musicManager.LoadMusic("daftLoop", "Assets/Sounds/SeikanHikou/DaftLoop.wav");
	std::string rankaFile = "Assets/Sprites/movie/ranka/ranka";
	for (int i = 1; i < 25; i++) {
		if (i < 10) {
			sozaiManager.makeSozai("", (rankaFile + "0" + std::to_string(i) + ".avi").c_str(), 640, 360);
		}
		else {
			sozaiManager.makeSozai("", (rankaFile + std::to_string(i) + ".avi").c_str(), 640, 360);
		}
		sozaiManager.setSozaiEx(i - 1, (2.0/3.0));
		sozaiManager.setMovieFlag(i - 1, true);
	}
	for (int i = 0; i < 24; i++) {
		sozaiManager.setReverseFlag(i, false);
		sozaiManager.setDrumFlag(i, false);
	}
	setSample(0);

	// 効果音読み込み
	SEHandle[0] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/pause.wav");
	SEHandle[1] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/cancel.wav");

	// とりあえずドラムならす
	ChangeVolumeSoundMem(255, musicManager.GetNowPlayingHandle());
	playBGM = true;
	musicManager.Play("daftLoop");
	// このハンドル渡す設計微妙すぎる
	noteManager.setBGMHandle(musicManager.GetNowPlayingHandle());
	noteManager.loadFromFile("Assets/Score/seikan.mhs");
	noteManager.startPlay();
}

void SceneSeikanHikou::update() {
	noteManager.update();
	if (!enablePause) {
		sozaiManager.update();
		if (Pad::getIns()->get(ePad::change) == 1) {
			if (playBGM) {
				playBGM = false;
				musicManager.Stop();
			}
			else {
				playBGM = true;
				musicManager.Play("daftLoop");
			}
		}

		// コントローラーとサンプルの対応を設定
		if (Pad::getIns()->get(ePad::L) >= 1) {
			if (sampleSetNum != 1) {
				sampleSetNum = 1;
				setSample(sampleSetNum);
			}
		}
		else if (Pad::getIns()->get(ePad::R) >= 1) {
			if (sampleSetNum != 2) {
				sampleSetNum = 2;
				setSample(sampleSetNum);
			}
		}
		else {
			if (sampleSetNum != 0) {
				sampleSetNum = 0;
				setSample(sampleSetNum);
			}
		}

		if (Pad::getIns()->get(ePad::start) == 1) {
			// ポーズ画面表示
			PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK, TRUE);
			musicManager.Stop();
			enablePause = true;
			pauseMenu.setActive();
			//pauseMenu.update();		普遍的なポーズの導入の仕方考えた方がいい
		}
	}
	else {
		// ポーズメニューの処理を行う
		pauseMenu.update();
		if (!pauseMenu.getActive()) {
			if (pauseMenu.getSelectCmd() == 0) {
				// メニューへ戻る
				PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK, TRUE);
				Parameter parameter;
				const bool stackClear = true;
				Sound::getIns()->release();
				Image::getIns()->release();
				_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
			}
			else {
				// ポーズメニュー終了
				musicManager.Play("daftLoop");
				enablePause = false;
			}
		}
	}
}

void SceneSeikanHikou::draw() const {
	sozaiManager.draw();
	if (enablePause) {
		pauseMenu.draw();
	}
	noteManager.draw();
}

void SceneSeikanHikou::resetSample() {
	for (int i = 0; i < 25; i++) {
		sozaiManager.resetSozaiKey(i);
	}
}

void SceneSeikanHikou::setSample(int num) {
	resetSample();
	switch (num) {
	case 0:
		sozaiManager.setSozaiKey(0, ePad::down, 0);
		sozaiManager.setSozaiKey(1, ePad::B, 0);
		sozaiManager.setSozaiKey(2, ePad::left, 0);
		sozaiManager.setSozaiKey(3, ePad::Y, 0);
		sozaiManager.setSozaiKey(4, ePad::up, 0);
		sozaiManager.setSozaiKey(5, ePad::X, 0);
		sozaiManager.setSozaiKey(6, ePad::right, 0);
		sozaiManager.setSozaiKey(7, ePad::A, 0);
		break;
	case 1:
		sozaiManager.setSozaiKey(8, ePad::down, 0);
		sozaiManager.setSozaiKey(9, ePad::B, 0);
		sozaiManager.setSozaiKey(10, ePad::left, 0);
		sozaiManager.setSozaiKey(11, ePad::Y, 0);
		sozaiManager.setSozaiKey(12, ePad::up, 0);
		sozaiManager.setSozaiKey(13, ePad::X, 0);
		sozaiManager.setSozaiKey(14, ePad::right, 0);
		sozaiManager.setSozaiKey(15, ePad::A, 0);
		break;
	case 2:
		sozaiManager.setSozaiKey(16, ePad::down, 0);
		sozaiManager.setSozaiKey(17, ePad::B, 0);
		sozaiManager.setSozaiKey(18, ePad::left, 0);
		sozaiManager.setSozaiKey(19, ePad::Y, 0);
		sozaiManager.setSozaiKey(20, ePad::up, 0);
		sozaiManager.setSozaiKey(21, ePad::X, 0);
		sozaiManager.setSozaiKey(22, ePad::right, 0);
		sozaiManager.setSozaiKey(23, ePad::A, 0);// キラッ☆
		break;
	}
}
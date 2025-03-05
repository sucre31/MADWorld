#include <DxLib.h>
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "SceneSeikanHikou.h"


SceneSeikanHikou::SceneSeikanHikou(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), sampleSetNum(0){
	// 素材の読み込み
	daftHandle = Sound::getIns()->loadSamples("Assets/Sounds/SeikanHikou/DaftLoop.wav");
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

	// とりあえずドラムならす
	ChangeVolumeSoundMem(200, daftHandle);
	PlaySoundMem(daftHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void SceneSeikanHikou::update() {
	sozaiManager.update();

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
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

void SceneSeikanHikou::draw() const {
	sozaiManager.draw();
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
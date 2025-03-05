#include <DxLib.h>
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "SceneSeikanHikou.h"


SceneSeikanHikou::SceneSeikanHikou(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), sampleSetNum(0){
	// ‘fÞ‚Ì“Ç‚Ýž‚Ý
	daftHandle = Sound::getIns()->loadSamples("Assets/Sounds/SeikanHikou/DaftLoop.wav");
	std::string rankaFile = "Assets/Sprites/movie/ranka/ranka";
	//sozaiManager.makeSozai("", "Assets/Sprites/movie/ranka/ranka01.avi", 640, 360);
	for (int i = 1; i < 26; i++) {
		if (i < 10) {
			sozaiManager.makeSozai("", (rankaFile + "0" + std::to_string(i) + ".avi").c_str(), 640, 360);
		}
		else {
			sozaiManager.makeSozai("", (rankaFile + std::to_string(i) + ".avi").c_str(), 640, 360);
		}
		sozaiManager.setSozaiEx(i - 1, (2.0/3.0));
		sozaiManager.setMovieFlag(i - 1, true);
	}
	setSample(0);
	for (int i = 0; i < 10; i++) {
		sozaiManager.setDrumFlag(i, false);
	}

	// ‚Æ‚è‚ ‚¦‚¸‚È‚ç‚·
	ChangeVolumeSoundMem(200, daftHandle);
	PlaySoundMem(daftHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void SceneSeikanHikou::update() {
	sozaiManager.update();

	if (Pad::getIns()->get(ePad::change) == 1) {
		sampleSetNum = (sampleSetNum + 1) % 3;
		setSample(sampleSetNum);
	}

	if (Pad::getIns()->get(ePad::start) == 1) {
		// ƒƒjƒ…[‚É–ß‚é
		Parameter parameter;
		const bool stackClear = true;
		// ‚±‚±‚É’¼Ú‘‚­‚ñ‚¶‚á‚È‚­‚ÄŠÖ”—pˆÓ‚·‚×‚«‚©‚È
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
		sozaiManager.setSozaiKey(i, -1, 0);
	}
}

void SceneSeikanHikou::setSample(int num) {
	//resetSample();
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
		sozaiManager.setSozaiKey(8, ePad::L, 0);
		sozaiManager.setSozaiKey(9, ePad::R, 0);
		break;
	case 1:
		sozaiManager.setSozaiKey(10, ePad::down, 0);
		sozaiManager.setSozaiKey(11, ePad::B, 0);
		sozaiManager.setSozaiKey(12, ePad::left, 0);
		sozaiManager.setSozaiKey(13, ePad::Y, 0);
		sozaiManager.setSozaiKey(14, ePad::up, 0);
		sozaiManager.setSozaiKey(15, ePad::X, 0);
		sozaiManager.setSozaiKey(16, ePad::right, 0);
		sozaiManager.setSozaiKey(17, ePad::A, 0);
		sozaiManager.setSozaiKey(18, ePad::L, 0);
		sozaiManager.setSozaiKey(19, ePad::R, 0);
		break;
	case 2:
		sozaiManager.setSozaiKey(20, ePad::down, 0);
		sozaiManager.setSozaiKey(21, ePad::B, 0);
		sozaiManager.setSozaiKey(22, ePad::left, 0);
		sozaiManager.setSozaiKey(23, ePad::Y, 0);
		sozaiManager.setSozaiKey(24, ePad::up, 0);
		sozaiManager.setSozaiKey(25, ePad::X, 0);
		break;
	}
}
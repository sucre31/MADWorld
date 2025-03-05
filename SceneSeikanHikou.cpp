#include <DxLib.h>
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "SceneSeikanHikou.h"


SceneSeikanHikou::SceneSeikanHikou(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
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
		sozaiManager.setMovieFlag(i - 1, true);
	}
	sozaiManager.setSozaiKey(0, ePad::down, 0);
	sozaiManager.setSozaiKey(1, ePad::left, 0);
	sozaiManager.setSozaiKey(2, ePad::up, 0);
	sozaiManager.setSozaiKey(3, ePad::right, 0);
	sozaiManager.setSozaiKey(4, ePad::Y, 0);
	sozaiManager.setSozaiKey(5, ePad::B, 0);
	sozaiManager.setSozaiKey(6, ePad::A, 0);
	sozaiManager.setSozaiKey(7, ePad::X, 0);
	sozaiManager.setSozaiKey(8, ePad::L, 0);
	sozaiManager.setSozaiKey(9, ePad::R, 0);
	for (int i = 0; i < 10; i++) {
		sozaiManager.setDrumFlag(i, false);
	}

	// ‚Æ‚è‚ ‚¦‚¸‚È‚ç‚·
	ChangeVolumeSoundMem(200, daftHandle);
	PlaySoundMem(daftHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void SceneSeikanHikou::update() {
	sozaiManager.update();

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
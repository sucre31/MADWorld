#include <DxLib.h>
#include "SceneAlice.h"
#include "Sound.h"
#include "Image.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"


SceneAlice::SceneAlice(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample0.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample1.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample2.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample3.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample4.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample5.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample6.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample7.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample8.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample9.avi", 640, 360);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample10.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample11.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample12.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample13.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample14.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample15.avi", 0, 0);
	sozaiManager.setSozaiKey(0, ePad::L, 0);
	sozaiManager.setSozaiKey(1, ePad::down, 0);
	sozaiManager.setSozaiKey(2, ePad::R, 0);
	sozaiManager.setSozaiKey(3, ePad::left, 0);
	sozaiManager.setSozaiKey(4, ePad::A, 0);
	sozaiManager.setSozaiKey(5, ePad::up, 0);
	sozaiManager.setSozaiKey(6, ePad::X, 0);
	sozaiManager.setSozaiKey(7, ePad::right, 0);
	sozaiManager.setSozaiKey(8, ePad::B, 0);
	sozaiManager.setSozaiKey(9, ePad::Y, 0);
	isMusicPlay = false;
	for (int i = 0; i < 10; i++) {
		sozaiManager.setSozaiEx(i, 0.25);
		sozaiManager.setSozaiPos(i, 160 + (i % 4) * 320, 90 + (i / 4) * 180);
	}
	aliceDrumHandle = Sound::getIns()->loadSamples("Assets/Sounds/Alice/drumNBass.wav");
}

void SceneAlice::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::change) == 1) {
		if (isMusicPlay) {
			isMusicPlay = false;
			StopSoundMem(aliceDrumHandle);
		}
		else {
			isMusicPlay = true;
			PlaySoundMem(aliceDrumHandle, DX_PLAYTYPE_LOOP, TRUE);
		}
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// ƒƒjƒ…[‚É–ß‚é
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(aliceDrumHandle);
		// ‚±‚±‚É’¼Ú‘‚­‚ñ‚¶‚á‚È‚­‚ÄŠÖ”—pˆÓ‚·‚×‚«‚©‚È
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

void SceneAlice::draw() const {
	sozaiManager.draw();
}
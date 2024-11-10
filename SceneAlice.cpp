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
	sozaiManager.setSozaiKey(0, ePad::L);
	sozaiManager.setSozaiKey(1, ePad::down);
	sozaiManager.setSozaiKey(2, ePad::R);
	sozaiManager.setSozaiKey(3, ePad::left);
	sozaiManager.setSozaiKey(4, ePad::A);
	sozaiManager.setSozaiKey(5, ePad::up);
	sozaiManager.setSozaiKey(6, ePad::X);
	sozaiManager.setSozaiKey(7, ePad::right);
	sozaiManager.setSozaiKey(8, ePad::B);
	sozaiManager.setSozaiKey(9, ePad::Y);
}

void SceneAlice::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::change) == 1) {
		PlaySoundMem(Sound::getIns()->getaliceDrumHandle(), DX_PLAYTYPE_LOOP, TRUE);
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// ƒƒjƒ…[‚É–ß‚é
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(Sound::getIns()->getaliceDrumHandle());
		// ‚±‚±‚É’¼Ú‘‚­‚ñ‚¶‚á‚È‚­‚ÄŠÖ”—pˆÓ‚·‚×‚«‚©‚È
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneAlice::draw() const {
	sozaiManager.draw();
}
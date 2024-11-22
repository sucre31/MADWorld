#include "SceneDontaco.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"

SceneDontaco::SceneDontaco(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	sozaiManager.makeSozai("Assets/Sounds/dontaco/don.wav", "Assets/Sprites/images/dontaco/dontacos.png", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/dontaco/taco.wav", "Assets/Sprites/images/dontaco/dontacos.png", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/dontaco/s.wav", "Assets/Sprites/images/dontaco/dontacos.png", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/dontaco/tara.wav", "Assets/Sprites/images/dontaco/dontacos.png", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/dontaco/taco2.wav", "Assets/Sprites/images/dontaco/dontacos.png", 640, 360);
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	sozaiManager.setSozaiKey(1, ePad::left, 0);
	sozaiManager.setSozaiKey(2, ePad::B, 0);
	sozaiManager.setSozaiKey(3, ePad::down, 0);
	sozaiManager.setSozaiKey(4, ePad::right, 0);
	for (int i = 0; i < 5; i++) {
		sozaiManager.setDrumFlag(i, true);
	}
}

void SceneDontaco::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::R) == 1) {
		// Rデスタッカート
		for (int i = 0; i < 5; i++) {
			sozaiManager.setPadReleaseStop(i, true);
		}
	}
	if (Pad::getIns()->get(ePad::R) == 0) {
		for (int i = 0; i < 5; i++) {
			sozaiManager.setPadReleaseStop(i, false);
		}
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneDontaco::draw() const {
	sozaiManager.draw();
}
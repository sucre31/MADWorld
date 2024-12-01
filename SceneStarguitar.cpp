#include "SceneStarguitar.h"
#include "Sound.h"
#include "Image.h"
#include "Define.h"

SceneStarguitar::SceneStarguitar(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	/*sozaiManager.makeSozai("Assets/sounds/Starguitar/snea.wav", "", Define::WIN_W / 2, Define::WIN_H / 2);
	sozaiManager.setReverseFlag(0, false);
	std::string snea = "Assets/Sprites/images/starguitar/snea/snea";
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	for (int i = 1; i < 30; i++) {
		sozaiManager.addSprites(0, (snea + std::to_string(i) + ".png").c_str());
	}

	sozaiManager.makeSozai("Assets/sounds/Starguitar/snea2.wav", "", Define::WIN_W / 2, Define::WIN_H / 2);
	sozaiManager.setSozaiKey(1, ePad::B, 0);
	sozaiManager.setReverseFlag(1, false);
	std::string sneaB = "Assets/Sprites/images/starguitar/sneaB/sneaB";
	for (int i = 1; i < 28; i++) {
		sozaiManager.addSprites(1, (sneaB + std::to_string(i) + ".png").c_str());
	}

	sozaiManager.makeSozai("Assets/sounds/Starguitar/kick.wav", "", Define::WIN_W / 2, Define::WIN_H / 2);
	sozaiManager.setSozaiKey(2, ePad::down, 0);

	for (int i = 0; i < 3; i++) {
		sozaiManager.setPlayRate(i, 50);
	}*/

	backGround.loadBackImage("Assets/Sprites/images/starguitar/back.png");
}


void SceneStarguitar::update() {
	starguitarDrums.update();
	//sozaiManager.update();
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

void SceneStarguitar::draw() const {
	backGround.draw();
	//sozaiManager.draw();
	starguitarDrums.draw();
}

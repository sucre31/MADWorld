#include "SceneStarguitar.h"
#include "Sound.h"
#include "Image.h"
#include "Define.h"

SceneStarguitar::SceneStarguitar(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	backGround.loadBackImage("Assets/Sprites/images/starguitar/back.png");
}


void SceneStarguitar::update() {
	starguitarDrums.update();
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
	starguitarDrums.draw();
}

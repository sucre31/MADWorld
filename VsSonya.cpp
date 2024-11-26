#include <Dxlib.h>
#include "VsSonya.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "Define.h"

VsSonya::VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	shiwakeMasterHandle = shiwakeMasterHandle = Sound::getIns()->loadBGM("Assets/Sounds/sonya/shiwakeMaster.wav");
	PlaySoundMem(shiwakeMasterHandle, DX_PLAYTYPE_LOOP, TRUE);
	sozaiManager.makeSozai("Assets/Sounds/sonya/hey.wav", "Assets/Sprites/images/sonya/yasuna/yasuna0.png", Define::WIN_W / 2, Define::WIN_H * 3 / 4 - 10);
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna2.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna3.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna4.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna0.png");
	sozaiManager.setReverseFlag(0, false);
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	prevTime = GetNowHiPerformanceCount();
}

void VsSonya::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime;

	sozaiManager.update();
	if (Pad::getIns()->get(ePad::right) >= 1) {
		if (deltaTime > 100) {
			prevTime = curTime;
			sozaiManager.changePos(0, 0.1, 0);
		}
	}
	if (Pad::getIns()->get(ePad::left) >= 1) {
		if (deltaTime > 100) {
			prevTime = curTime;
			sozaiManager.changePos(0, -0.1, 0);
		}
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// ƒƒjƒ…[‚É–ß‚é
		Parameter parameter;
		const bool stackClear = true;
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

void VsSonya::draw() const{
	sozaiManager.draw();
}
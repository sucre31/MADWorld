#include <Dxlib.h>
#include "VsSonya.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "Define.h"


VsSonya::VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	shiwakeMasterHandle = shiwakeMasterHandle = Sound::getIns()->loadBGM("Assets/Sounds/sonya/shiwakeMaster.wav");
	PlaySoundMem(shiwakeMasterHandle, DX_PLAYTYPE_LOOP, TRUE);
	sozaiManager.makeSozai("Assets/Sounds/sonya/hey.wav", "Assets/Sprites/images/sonya/yasuna/yasuna0.png", Define::WIN_W * 3 / 4, Define::WIN_H * 3 / 4 - 40);
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna2.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna3.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna4.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna0.png");
	sozaiManager.addSound(0, "Assets/Sounds/sonya/sukiari.wav");
	sozaiManager.setReverseFlag(0, false);
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	sozaiManager.setSozaiKey(0, ePad::B, 1);
	sozaiManager.setSozaiEx(0, 1.25);

	sozaiManager.makeSozai("Assets/Sounds/sonya/tto.wav", "Assets/Sprites/images/sonya/sonya/sonya0.png", Define::WIN_W * 1 / 4, Define::WIN_H * 3 / 4 - 40);
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya1.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya2.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya3.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya4.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya0.png");
	sozaiManager.setReverseFlag(1, false);
	sozaiManager.setSozaiKey(1, ePad::right, 0);
	sozaiManager.setSozaiEx(1, 0.75);

	// ”wŒi‚ÌÝ’è
	sideBarR.setPosX(1120);
	backGround[0].loadBackImage("Assets/Sprites/images/sonya/sky.png");
	backGround[1].loadBackImage("Assets/Sprites/images/sonya/house.png");
	backGround[2].loadBackImage("Assets/Sprites/images/sonya/bush.png");
	backGround[3].loadBackImage("Assets/Sprites/images/sonya/wall.png");
	backGround[4].loadBackImage("Assets/Sprites/images/sonya/denchu.png");

	prevTime = GetNowHiPerformanceCount();
}

void VsSonya::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime;

	sozaiManager.update();
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
	for (int i = 0; i < backgroundNum; i++) {
		backGround[i].draw();
	}
	sozaiManager.draw();
	sideBarL.draw();
	sideBarR.draw();

}
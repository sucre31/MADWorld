#include <memory>
#include <Dxlib.h>
#include "VsSonya.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "Define.h"
#include "snowBall.h"


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
	sozaiManager.addSound(0, "");
	sozaiManager.setReverseFlag(0, false);
	sozaiManager.setSozaiKey(0, ePad::right, 0);
	sozaiManager.setSozaiKey(0, ePad::down, 1);
	sozaiManager.setSozaiKey(0, ePad::up, 2);
	sozaiManager.setSozaiEx(0, 1.25);
	sozaiManager.setMultiSound(0, true);

	sozaiManager.makeSozai("Assets/Sounds/sonya/tto.wav", "Assets/Sprites/images/sonya/sonya/sonya0.png", Define::WIN_W * 1 / 4, Define::WIN_H * 3 / 4 - 40);
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya1.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya2.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya3.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya4.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya0.png");
	sozaiManager.setReverseFlag(1, false);
	sozaiManager.setSozaiKey(1, ePad::A, 0);
	sozaiManager.setSozaiEx(1, 0.75);

	// 背景の設定
	sideBarR.setPosX(1120);
	backGround[0].loadBackImage("Assets/Sprites/images/sonya/sky.png");
	backGround[1].loadBackImage("Assets/Sprites/images/sonya/house.png");
	backGround[2].loadBackImage("Assets/Sprites/images/sonya/bush.png");
	backGround[3].loadBackImage("Assets/Sprites/images/sonya/wall.png");
	backGround[4].loadBackImage("Assets/Sprites/images/sonya/denchu.png");

	debugSEHandle = Sound::getIns()->loadSamples("Assets/Sounds/sonya/tto.wav");

	prevTime = GetNowHiPerformanceCount();

	showBar = true;
}

void VsSonya::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime;

	sozaiManager.update();

	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}

	if (Pad::getIns()->get(ePad::R) == 1) {
		showBar = !showBar;
	}

	if (Pad::getIns()->get(ePad::down) == 1) {
		makeSnowBall();
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		makeSnowBall();
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		makeSnowBall();
	}
	for (int i = 0; i < snowBallPtr.size(); i++) {
		snowBallPtr[i]->update();
		if (snowBallPtr[i]->getState() == 1) {
			sozaiManager.playSozai(1, 0);
			snowBallPtr[i]->setState(2);
		}
		if (snowBallPtr[i]->getState() == 3) {
			snowBallPtr.erase(snowBallPtr.begin() + i);
			i--;
		}
	}
}

void VsSonya::makeSnowBall() {
	// 雪玉のインスタンス生成 いちいち作らずに使いまわすべきかも
	snowBallPtr.push_back(std::make_unique<snowBall>());
	snowBallPtr[snowBallPtr.size() - 1]->setSEHandle(debugSEHandle);
}

void VsSonya::draw() const{
	for (int i = 0; i < backgroundNum; i++) {
		backGround[i].draw();
	}
	sozaiManager.drawSozai(1);
	for (int i = 0; i < snowBallPtr.size(); i++) {
		snowBallPtr[i]->draw();
	}
	sozaiManager.drawSozai(0);
	if (showBar) {
		sideBarL.draw();
		sideBarR.draw();
	}

}
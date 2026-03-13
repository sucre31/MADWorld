#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	float exRate = 3.75;
	backGround[0].loadBackImage("Assets/Sprites/images/phoenixWright/others/courtBack1.png");
	backGround[1].loadBackImage("Assets/Sprites/images/phoenixWright/others/courtBack2.png");

	backGround[0].setExRate(exRate);
	backGround[1].setExRate(exRate);

	// ナルホド
	int naruhodoPosY = (Define::WIN_W / 2.0) + 4;
	int naruhodoPosX = (Define::WIN_H / 2.0) - 65;
	sozaiManager.makeSozai("", "Assets/Sprites/images/phoenixWright/naruhodo/idle/idle0.png", naruhodoPosY, naruhodoPosX);
	sozaiManager.addSound(0, "Assets/Sounds/phoenixWright/naruhodo/objection.wav");
	for (int i = 0; i < 12; i++) {
		sozaiManager.addSprite(0, 1, ("Assets/Sprites/images/phoenixWright/naruhodo/objection/objection" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager.addSound(0, "Assets/Sounds/phoenixWright/bass.wav");
	for (int i = 0; i < 7; i++) {
		sozaiManager.addSprite(0, 2, ("Assets/Sprites/images/phoenixWright/naruhodo/bass/bass" + std::to_string(i) + ".png").c_str());
	}

	// ミツルギ
	int mitsurugiOffset = 53;
	sozaiManager.makeSozai("", "Assets/Sprites/images/phoenixWright/mitsurugi/idle/idle0.png", (Define::WIN_W / 2.0) + 60, (Define::WIN_H / 2.0) + mitsurugiOffset);
	for (int i = 0; i < 3; i++) {
		sozaiManager.addSprite(1, 0, ("Assets/Sprites/images/phoenixWright/mitsurugi/idle/idle" + std::to_string(i) + ".png").c_str());
	}
	sozaiManager.addSound(1, "Assets/Sounds/phoenixWright/mitsurugi/objection.wav");
	for (int i = 0; i < 8; i++) {
		sozaiManager.addSprite(1, 1, ("Assets/Sprites/images/phoenixWright/mitsurugi/objection/objection" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager.addSound(1, "Assets/Sounds/phoenixWright/bass.wav");
	for (int i = 0; i < 6; i++) {
		sozaiManager.addSprite(1, 2, ("Assets/Sprites/images/phoenixWright/mitsurugi/bass/bass" + std::to_string(i) + ".png").c_str());
	}

	// テーブル
	int tableOffSet = 64;
	sozaiManager.makeSozai("", "Assets/Sprites/images/phoenixWright/others/table.png", (Define::WIN_W / 2.0), naruhodoPosX + tableOffSet);
	sozaiManager.setSozaiLayer(2, 1);

	for (int i = 0; i < 3; i++) {
		sozaiManager.setSozaiEx(i, exRate);
		sozaiManager.setReverseFlag(i, false);
	}

	setKey();
}

void SceneSecondRemix::update() {
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	for (int i = 0; i < 1; i++) {
		backGround[i].draw();
	}
	sozaiManager.draw();
}

void SceneSecondRemix::setKey() {
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	sozaiManager.setSozaiKey(0, ePad::B, 1);
	sozaiManager.setSozaiKey(0, ePad::Y, 2);
	sozaiManager.setSozaiKey(1, ePad::up, 0);
	sozaiManager.setSozaiKey(1, ePad::right, 1);
	sozaiManager.setSozaiKey(1, ePad::down, 2);
}
#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	sozaiManager.makeSozai("", "Assets/Sprites/images/phoenixWright/naruhodo/idle/idle0.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager.addSound(0, "Assets/Sounds/phoenixWright/naruhodo/objection.wav");
	for (int i = 0; i < 12; i++) {
		sozaiManager.addSprite(0, 1, ("Assets/Sprites/images/phoenixWright/naruhodo/objection/objection" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager.addSound(0, "Assets/Sounds/phoenixWright/bass.wav");
	for (int i = 0; i < 4; i++) {
		sozaiManager.addSprite(0, 2, ("Assets/Sprites/images/phoenixWright/naruhodo/bass/bass" + std::to_string(i) + ".png").c_str());
	}


	sozaiManager.setSozaiEx(0, 3.0);
	sozaiManager.setReverseFlag(0, false);
	setKey();
}

void SceneSecondRemix::update() {
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
}

void SceneSecondRemix::setKey() {
	sozaiManager.setSozaiKey(0, ePad::A, 0);
	sozaiManager.setSozaiKey(0, ePad::B, 1);
	sozaiManager.setSozaiKey(0, ePad::Y, 2);
}
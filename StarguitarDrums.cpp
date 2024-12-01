#include <string>
#include "StarguitarDrums.h"
#include "Define.h"

StarguitarDrums::StarguitarDrums() {
	sozai[0].setSampleSound("Assets/sounds/Starguitar/snea.wav");
	std::string snea = "Assets/Sprites/images/starguitar/snea/snea";
	for (int i = 0; i < 30; i++) {
		sozai[0].addSprite((snea + std::to_string(i) + ".png").c_str());
	}

	sozai[1].setSampleSound("Assets/sounds/Starguitar/snea2.wav");
	sozai[1].addSprite("Assets/sounds/Starguitar/snea.wav");
	std::string sneaB = "Assets/Sprites/images/starguitar/sneaB/sneaB";
	for (int i = 1; i < 30; i++) {
		sozai[1].addSprite((sneaB + std::to_string(i) + ".png").c_str());
	}

	sozai[2].setSampleSound("Assets/sounds/Starguitar/kick.wav");

	for (int i = 0; i < drumNum; i++) {
		sozai[i].setUseTurn(false);
		sozai[i].setPosX(Define::WIN_W / 2);
		sozai[i].setPosY(Define::WIN_H / 2);
		sozai[i].setPlayRate(50);
		sozai[i].setEnableMultiMovie(true);
	}
}

bool StarguitarDrums::update() {
	for (int i = 0; i < drumNum; i++) {
		sozai[i].update();
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		sozai[0].playWithSoundIndex(0);
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		sozai[1].playWithSoundIndex(0);
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		sozai[2].playWithSoundIndex(0);
	}
	return true;
}

void StarguitarDrums::draw() const {
	for (int i = 0; i < drumNum; i++) {
		sozai[i].draw();
	}
}
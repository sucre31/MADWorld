#include <Dxlib.h>
#include "sideBlank.h"
#include "Image.h"

sideBlank::sideBlank(): breakState(0) {
	posX = 0;
	posY = 0;
	imageHandle[0] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar1.png");
	imageHandle[1] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar2.png");
	imageHandle[2] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar3.png");
	imageHandle[3] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar4.png");
	imageHandle[4] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar5.png");
	imageHandle[5] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar6.png");
	imageHandle[6] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar7.png");
	imageHandle[7] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar8.png");
	imageHandle[8] = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar9.png");
}

bool sideBlank::update() {
	return true;
}

void sideBlank::draw() const {
	DrawGraph(posX, posY, imageHandle[breakState], TRUE);
}

void sideBlank::setState(int state) {
	if (state >= 0 && state < imageNum) {
		breakState = state;
	}
}
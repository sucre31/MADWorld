#include <Dxlib.h>
#include "sideBlank.h"
#include "Image.h"

sideBlank::sideBlank() {
	posX = 0;
	posY = 0;
	imageHandle = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/sideBar.png");
}

bool sideBlank::update() {
	return true;
}

void sideBlank::draw() const {
	DrawGraph(posX, posY, imageHandle, TRUE);
}
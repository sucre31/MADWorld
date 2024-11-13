#include "Dxlib.h"
#include "BackGround.h"

BackGround::BackGround() {

}

void BackGround::loadBackImage(const char* imageFileName) {
	backGroundHandle = Image::getIns()->loadSamples(imageFileName);
}

bool BackGround::update() {
	return true;
}

void BackGround::draw() const {
	DrawRotaGraph(640, 360, (2.0 / 3.0), 0, backGroundHandle, FALSE, FALSE);
}
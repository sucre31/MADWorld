#include "Dxlib.h"
#include "Define.h"
#include "BackGround.h"

BackGround::BackGround() {
	exRate = 1.0;
}

void BackGround::loadBackImage(const char* imageFileName) {
	backGroundHandle = Image::getIns()->loadSamples(imageFileName);
}

bool BackGround::update() {
	return true;
}

void BackGround::draw() const {
	DrawRotaGraph(Define::WIN_W / 2, Define::WIN_H / 2, exRate, 0, backGroundHandle, FALSE, FALSE);
}
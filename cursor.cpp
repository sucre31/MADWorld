#include <Dxlib.h>
#include "Image.h"
#include "cursor.h"
#include "Define.h"

cursor::cursor() {
	posX = Define::WIN_W / 2;
	posY = Define::WIN_H / 2;
}

bool cursor::update() {
	return true;
}

void cursor::draw() const {
	DrawRotaGraph((int)(posX + 16), (int)(posY + 16), 1.0, 0.0, myGraphHandle, true, false);
}

void cursor::loadCurorImage(const char* imageFileName) {
	myGraphHandle = Image::getIns()->loadSamples(imageFileName);
}

void cursor::plusPos(double x, double y) {
	posX += x;
	posY += y;
	if (posX < 0) {
		posX = 0;
	}
	if (posX > Define::WIN_W) {
		posX = Define::WIN_W;
	}
	if (posY < 0) {
		posY = 0;
	}
	if (posY > Define::WIN_H) {
		posY = Define::WIN_H;
	}

}
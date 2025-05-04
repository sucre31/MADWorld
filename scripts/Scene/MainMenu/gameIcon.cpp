#include <Dxlib.h>
#include "gameIcon.h"
#include "Common/Image.h"

gameIcon::gameIcon() :isCursorOn(false), thumbnailRate(defaultExRate), enableIcon(false) {
}

bool gameIcon::update() {
	if (isCursorOn) {
		thumbnailRate -= 0.01;
	}
	else {
		thumbnailRate += 0.01;
	}
	if (thumbnailRate < defaultExRate) {
		thumbnailRate = defaultExRate;
	}
	return true;
}

void gameIcon::draw() const{
	if (enableIcon) {
		if (isCursorOn) {
			unsigned int hitColor = GetColor(255, 0, 0);
			int boxPosX1 = posX - defaultHitW / 2;
			int boxPosY1 = posY - defaultHitH / 2;
			DrawBox(boxPosX1 - 3, boxPosY1 - 3, boxPosX1 + defaultHitW + 3, boxPosY1 + defaultHitH + 3, hitColor, TRUE);
		}
		DrawRotaGraph(posX, posY, thumbnailRate, 0.0, thumbnailHandle, FALSE, FALSE);
	}
}

void gameIcon::loadThumbnail(const char* imageFileName) {
	thumbnailHandle = Image::getIns()->loadSamples(imageFileName);
}

bool gameIcon::checkCursorHit(int x, int y) {
	if ((posX - defaultHitW / 2) - x > 0) {
		isCursorOn = false;
		return isCursorOn;
	}
	if ((posX + defaultHitW / 2) - x < 0) {
		isCursorOn = false;
		return isCursorOn;
	}
	if ((posY - defaultHitH / 2) - y > 0) {
		isCursorOn = false;
		return isCursorOn;
	}
	if ((posY + defaultHitH / 2) - y < 0) {
		isCursorOn = false;
		return isCursorOn;
	}
	isCursorOn = true;
	return isCursorOn;
}
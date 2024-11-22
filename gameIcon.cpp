#include <Dxlib.h>
#include "gameIcon.h"
#include "Image.h"

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
		DrawRotaGraph(posX, posY, thumbnailRate, 0.0, thumbnailHandle, FALSE, isCursorOn);
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
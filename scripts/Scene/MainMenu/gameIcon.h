#pragma once
#include "Common/GameObject/GameObject.h"

class gameIcon : public GameObject
{
public:
	gameIcon();
	~gameIcon() = default;
	bool update() override;
	void draw() const override;
	void loadThumbnail(const char* imageFileName);
	void enableIconFunc(bool flag) { enableIcon = flag; };
	void setPos(int x, int y) { posX = x, posY = y; }
	bool checkCursorHit(int x, int y);
private:
	const double defaultExRate = 0.6;
	const int imageWidth = 320;
	const int imageHeight = 180;
	const int defaultHitW = (int)(imageWidth * defaultExRate);
	const int defaultHitH = (int)(imageHeight * defaultExRate);
	bool enableIcon;
	int posX;
	int posY;
	int thumbnailHandle;
	double thumbnailRate;
	bool isCursorOn;

};


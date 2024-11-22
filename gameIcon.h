#pragma once
#include "GameObject.h"

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
	const int defaultHitW = 192;
	const int defaultHitH = 108;
	bool enableIcon;
	int posX;
	int posY;
	int thumbnailHandle;
	double thumbnailRate;
	bool isCursorOn;
};


#pragma once
#include "GameObject.h"
class cursor : public GameObject
{
public:
	cursor();
	~cursor() = default;
	void plusPos(double x, double y);
	bool update() override;
	void draw() const override;
	void loadCursorImage(const char* imageFileName);
	int getCursorPosX() { return posX; }
	int getCursorPosY() { return posY; }
private:
	int myGraphHandle;
	double posX;
	double posY;
};


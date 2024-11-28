#pragma once
#include "GameObject.h"
class sideBlank : public GameObject
{
public:
	sideBlank();
	~sideBlank() = default;
	bool update() override;
	void draw() const override;
	void setState(int state);
public:
	static const int imageNum = 9;
	int imageHandle[imageNum];
	int breakState;
};


#pragma once
#include "GameObject.h"
class sideBlank : public GameObject
{
public:
	sideBlank();
	~sideBlank() = default;
	bool update() override;
	void draw() const override;
public:
	int imageHandle;
};


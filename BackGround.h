#pragma once
#include "GameObject.h"
#include "Image.h"

class BackGround : public GameObject
{
public:
	BackGround();
	~BackGround() = default;
	bool update() override;
	void draw() const override;
	void loadBackImage(const char* imageFileName);
private:
	int backGroundHandle;
};

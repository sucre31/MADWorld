#pragma once
#include <vector>
#include <Dxlib.h>
#include "GameObject.h"
#include "Sozai.h"

// スターギター用に素材を管理する
class StarguitarDrums : public GameObject
{
public:
	StarguitarDrums();
	~StarguitarDrums() = default;
	bool update() override;
	void draw() const override;
private:
	static const int drumNum = 3;
	Sozai sozai[drumNum];
};


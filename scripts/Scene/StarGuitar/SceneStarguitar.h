#pragma once
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "StarguitarDrums.h"
#include "Common/GameObject/BackGround.h"

class SceneStarguitar : public AbstractScene
{
public:
	SceneStarguitar(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneStarguitar() = default;
	void update() override;
	void draw() const override;
private:
	SozaiManager sozaiManager;
	BackGround backGround;
	StarguitarDrums starguitarDrums;
};


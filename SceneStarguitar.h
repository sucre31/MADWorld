#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"

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
};


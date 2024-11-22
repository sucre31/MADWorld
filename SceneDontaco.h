#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class SceneDontaco : public AbstractScene
{
public:
	SceneDontaco(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneDontaco() = default;
	void update() override;
	void draw() const override;
private:
	SozaiManager sozaiManager;
};


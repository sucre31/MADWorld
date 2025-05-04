#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class SceneKajioh : public AbstractScene
{
public:
	SceneKajioh(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneKajioh() = default;
	void update() override;
	void draw() const override;
private:
	SozaiManager sozaiManager;
};


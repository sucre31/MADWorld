#pragma once
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
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


#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class SceneSeikanHikou : public AbstractScene
{
public:
	SceneSeikanHikou(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneSeikanHikou() = default;
	void update() override;
	void draw() const override;
private:
	int daftHandle; // ‚Æ‚è‚ ‚¦‚¸
	SozaiManager sozaiManager;
};


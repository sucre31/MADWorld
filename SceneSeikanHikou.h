#pragma once

#include "SozaiManager.h"
#include "PauseMenu.h"

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
	int sampleSetNum;
	void setSample(int);
	void resetSample();
	bool enablePause;
	int SEHandle[2];
	PauseMenu pauseMenu;
};


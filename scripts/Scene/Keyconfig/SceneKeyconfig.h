#pragma once
#include "System/AbstractScene.h"
class SceneKeyconfig : public AbstractScene
{
public:
	SceneKeyconfig(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneKeyconfig() = default;
	void update() override;
	void draw() const override;
private:
	int selectPadNum;
	bool setKeyChange;
	bool isWaitingForKeyChange;
};


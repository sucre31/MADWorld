#pragma once
#include "System/AbstractScene.h"
#include "RealTimeSequencer.h"
#include "Common/GameObject/SozaiManager.h"
class SceneRealEdit : public AbstractScene
{
public:
	SceneRealEdit(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~SceneRealEdit() = default;
	void update() override;
	void draw() const override;
private:
	SozaiManager sozaiManager;
	RealTimeSequencer sequencer;
};


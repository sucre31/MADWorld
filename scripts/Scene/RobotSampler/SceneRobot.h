#pragma once
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"

class SceneRobot : public AbstractScene
{
public:
	SceneRobot(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneRobot() = default;
	void update() override;
	void draw() const override;
private:
	void setKey();
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	std::unordered_map<int, int> sozaiHandles;

	bool gbFlag = false;
};


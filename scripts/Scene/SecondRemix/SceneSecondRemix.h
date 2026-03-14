#pragma once
#include <DxLib.h>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/GameObject/BackGround.h"
#include "ObjectionManager.h"
#include "DonesiaManager.h"


class SceneSecondRemix : public AbstractScene
{
public:
	SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneSecondRemix() = default;
	void update() override;
	void draw() const override;
private:
	ObjectionManager objectionManager;
	DonesiaManager donesiaManager;
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;
};


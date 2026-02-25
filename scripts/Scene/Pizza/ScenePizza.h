#pragma once
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"

class ScenePizza : public AbstractScene
{
public:
	ScenePizza(IOnSceneChangedListener* impl, const Parameter& parameter);
	~ScenePizza() = default;
	void update() override;
	void draw() const override;
private:
	void setKey();
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;
	int SEHandle[2];
};


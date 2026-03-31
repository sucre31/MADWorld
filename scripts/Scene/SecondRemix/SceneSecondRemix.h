#pragma once
#include <DxLib.h>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/GameObject/BackGround.h"
#include "SozaiObjection.h"
#include "SozaiDonesia.h"
#include "SozaiDontaco.h"
#include "SonyaManager.h"


class SceneSecondRemix : public AbstractScene
{
public:
	SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneSecondRemix() = default;
	void update() override;
	void draw() const override;
private:
	std::vector<SozaiBase*> sozaies;
	SozaiObjection objectionManager;
	SozaiDonesia donesiaManager;
	SozaiDontaco dontacoManager;
	SonyaManager sonyaManager;
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	std::string bgmName;
	int activeManagerIndex;
	int prevMangerIndex;
};


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
#include "DontacoManager.h"
#include "SonyaManager.h"


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
	DontacoManager dontacoManager;
	SonyaManager sonyaManager;
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	std::string bgmName;
	const int sozaiManagerCount = 3; // 一時的な確認用
	int activeManagerIndex;
};


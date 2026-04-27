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
#include "SozaiShuzo.h"
#include "SozaiSonya.h"


class SceneSecondRemix : public AbstractScene
{
public:
	SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneSecondRemix() = default;
	void update() override;
	void draw() const override;
private:
	std::vector<SozaiBase*> sozaies;
	SozaiObjection objection;
	SozaiDonesia donesia;
	SozaiDontaco dontaco;
	SozaiSonya sonya;
	SozaiShuzo shuzo;
	SozaiManager sozaiManager;
	NoteManager noteManager;
	std::shared_ptr<BPMManager> bpmManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	std::string bgmName;
	int activeManagerIndex;
	int prevMangerIndex;

	double currentBeat = -1;

	enum ActionType {
		SozaiChange,
		AutoPlay
	};

	struct SozaiEvent {
		int beat;          // 発火タイミング
		ActionType actionType;    // 何するか
		int param;
		bool triggered;    // 1回だけ用
	};

	std::vector<SozaiEvent> events;
};


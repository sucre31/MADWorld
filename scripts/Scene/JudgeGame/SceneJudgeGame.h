#pragma once
#include "System/AbstractScene.h"
#include "Common/Event/ActionRegistry.h"
#include "Common/Event/TimedEvent.h"
#include "Common/BPMManager.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/NoteManager.h"

class SceneJudgeGame : public AbstractScene
{
	// jsonベースで譜面・画面配置などの情報を読み込み、
	// 任意のリズムゲームをプレイできるシーン
	// 一旦楽曲・素材情報をjsonで読み込むところを作る
	// その後、譜面に合わせて再生や判定を作っていく
public:
	SceneJudgeGame(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~SceneJudgeGame() = default;
	void update() override;
	void draw() const override;
private:
	SozaiManager sozaiManager;
	std::unique_ptr<NoteManager> noteManager;
	
	ActionRegistry actionRegistry;
	std::vector<TimedEvent> events;
	BPMManager bpmManager;

	int bgmHandle = -1;

	void registerActions();
	void loadFromJson(const std::string& path);
};


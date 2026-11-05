#pragma once
#include "System/AbstractScene.h"
#include "Common/Event/ActionRegistry.h"
#include "Common/Event/TimedEvent.h"
#include "Common/BPMManager.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/NoteUIManager.h"

enum class eGameState {
	Ready,   // 開始前の待機
	Playing, // プレイ中
	Result   // リザルト画面
};

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
	eGameState currentState;
	int stateStartTime;
	int resultTimeCounter = 0;

	SozaiManager sozaiManager;
	std::unique_ptr<NoteManager> noteManager;
	std::unique_ptr<NoteUIManager> noteUIManager;
	
	ActionRegistry actionRegistry;
	std::vector<TimedEvent> events;
	BPMManager bpmManager;

	int bgmHandle = -1;

	void registerActions();
	void loadFromJson(const std::string& path);

	double beatDurationMs;  // 1拍の長さ
	int countdownDurationMs;// 4拍分の長さ
};


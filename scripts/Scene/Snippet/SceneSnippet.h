#pragma once

#include <memory>
#include "System/AbstractScene.h"
#include "StatusWindow.h"
#include "BackImage.h"
#include "Enemy.h"
#include "BeatManager.h"
#include "MessageWindow.h"
#include "EnemyManager.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"
#include "SnippetImage.h"
#include "Common/Event/ActionRegistry.h"
#include "Common/Event/TimedEvent.h"
#include "Common/Event/EventLoader.h"
#include "Common/BPMManager.h"
#include "PlayerCharacterManager.h"
#include "PopupNumberManager.h"

class StatusWindowManager;


class SceneSnippet : public AbstractScene
{
public:
	const static char* ParameterTagStage;
	const static char* ParameterTagLevel;

	SceneSnippet(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~SceneSnippet() = default;

	void update() override;
	void draw() const override;

private:
	int musicNumber;
	void initWindow();
	void setEnemyInstancetToCharacter();
	void initCharacter();
	std::shared_ptr<PlayerCharacterManager> playerManager;
	std::shared_ptr<StatusWindowManager> statusManager;
	EnemyManager* enemyManager;

	bool bgmStart;

	void initEventSystem();
	void registerActions();
	ActionRegistry registry;
	std::vector<TimedEvent> events;

	BPMManager bpmManager;

	std::shared_ptr<StatusWindow> _statusWindowA;
	std::shared_ptr<StatusWindow> _statusWindowB;
	std::shared_ptr<StatusWindow> _statusWindowC;
	std::shared_ptr<StatusWindow> _statusWindowD;
	std::shared_ptr<BackImage> _backImage;
	std::shared_ptr<BeatManager> beatManager;
	MessageWindow* messageWindow;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
	std::shared_ptr<SnippetImage> snippetImage;
	std::shared_ptr<PopupNumberManager> popUpManager;
};


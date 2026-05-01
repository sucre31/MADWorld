#pragma once
#include "Common/GameObject/GameObject.h"
#include "Enemy.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"
#include "SnippetImage.h"
#include "PlayerCharacterManager.h"

class StatusWindowManager;



class EnemyManager : GameObject
{
public:
	EnemyManager(
		std::shared_ptr<SnippetGameManager> managerIns, 
		std::shared_ptr<SnippetImage> imgIns, 
		std::shared_ptr<SnippetSound> sound, 
		std::shared_ptr<PlayerCharacterManager> player,
		std::shared_ptr<StatusWindowManager> window
	);
	~EnemyManager() = default;
	bool update() override;
	void draw() const override;
	void drawSecond() const;
	Enemy* getEnemyIns(int num);
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetSound(std::shared_ptr<SnippetSound> ins) { snippetSound = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	static const int NumberOfEnemy = 8;
	static const int NumberOfKind = 13;
	Enemy* enemy[NumberOfEnemy];
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
	std::shared_ptr<SnippetImage> snippetImage;
	std::shared_ptr<PlayerCharacterManager> playerManager;
	std::shared_ptr<StatusWindowManager> statusManager;
};


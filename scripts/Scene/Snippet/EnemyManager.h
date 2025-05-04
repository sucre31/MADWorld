#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"
#include "SnippetImage.h"

class EnemyManager : GameObject
{
public:
	EnemyManager();
	~EnemyManager() = default;
	bool update() override;
	void draw() const override;
	void drawSecond() const;
	Enemy* getEnemyIns(int num) { return enemy[num]; }
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetSound(std::shared_ptr<SnippetSound> ins) { snippetSound = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	static const int NumberOfEnemy = 8;
	static const int NumberOfKind = 5;
	Enemy* enemy[NumberOfEnemy];
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
	std::shared_ptr<SnippetImage> snippetImage;
};


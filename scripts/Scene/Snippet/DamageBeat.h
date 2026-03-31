#pragma once
#include <memory>
#include <vector>
#include "Common/GameObject/GameObject.h"
#include "DamageCharacter.h"
#include "SnippetGameManager.h"
#include "SnippetImage.h"

class DamageBeat : GameObject
{
public:
	DamageBeat();
	~DamageBeat() = default;
	bool update() override;
	void draw() const override;
	void addDamage(int valueOfDamage, bool isFast, int EnemyPosX, int EnemyPosY);
	void calcDamagePos();
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	int numberOfDamage;
	int ShowDamageHit;				//ボタンが押されたときのヒットエフェクト 0はださない
	int DamageHitPosX;
	int DamageHitPosY;
	std::vector<DamageCharacter*> damageNumber;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetImage> snippetImage;
};


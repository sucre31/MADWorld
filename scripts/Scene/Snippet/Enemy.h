#pragma once
#include <memory>
#include "Common/GameObject/GameObject.h"
#include "DamageBeat.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"
#include "SnippetImage.h"

class StatusWindowManager;

class PlayerCharacterManager;

enum eEnemy
{
	batty, pig, spider, rocket
};

enum class DeathType {
	Normal,
	Boss
};

class Enemy : public GameObject
{
public:
	Enemy(
		int x, int y,
		std::shared_ptr<SnippetGameManager> gameManager,
		std::shared_ptr<SnippetImage> image,
		std::shared_ptr<SnippetSound> sound,
		std::shared_ptr<PlayerCharacterManager> player,
		std::shared_ptr<StatusWindowManager> window
		);
	~Enemy() = default;
	bool update() override;
	void draw() const override;
	void drawSecond() const;
	void attack(int targetId, int damage);
	void setNewEnemy(int EnemyID);
	void setNextEnemyId(int id) { nextEnemyId = id; }
	void setDeathType(DeathType type);
	int getNextEnemyId() { return nextEnemyId; }
	void setEnemySoundIndex(int soundHandle);
	void setAlive(bool alive);
	void setAttackFlash(bool flash);
	bool isDeadFinished() const { return (!alive && deadTime >= deadDuration);}
	void getDamage(int valueOfDamage, bool isEarly);
	void getSize();
	int getID() const { return myID; }
	bool getAlive() const { return alive; }
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetSound(std::shared_ptr<SnippetSound> ins) { snippetSound = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
	void setPlayerManager(std::shared_ptr<PlayerCharacterManager> ins) { playerManager = ins; };
private:
	int myID;
	int HP;
	int myX, myY;
	int enemyImageX, enemyImageY;
	int BeatedMoveX;
	int count;
	int frameFromBeatTime;
	int attackSoundHandleIndex;
	bool reverseFlag;
	bool isBeated;
	bool alive;

	DeathType deathType = DeathType::Normal;
	double deadTime = 0.0;
	double deadDuration = 0.5; // 表示しておく時間（秒）

	bool attackFlash = false;
	double attackFlashTime = 0.0;
	double attackFlashDuration = 0.4; // 0.3秒とか

	int screen;
	int nextEnemyId = -1;
	std::unique_ptr<DamageBeat> damageBeat;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
	std::shared_ptr<SnippetImage> snippetImage;
	std::shared_ptr<PlayerCharacterManager> playerManager;
	std::shared_ptr<StatusWindowManager> statusManager;
};


#pragma once
#include <memory>
#include "GameObject.h"
#include "DamageBeat.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"
#include "SnippetImage.h"

enum eEnemy
{
	batty, pig, spider, rocket
};

class Enemy : public GameObject
{
public:
	Enemy(int x, int y);
	~Enemy() = default;
	bool update() override;
	void draw() const override;
	void drawSecond() const;
	void setNewEnemy(int EnemyID);
	void getDamage(int valueOfDamage, bool isEarly);
	void getSize();
	int getID() const { return myID; }
	bool getAlive() const { return alive; }
private:
	int myID;
	int HP;
	int myX, myY;
	int enemyImageX, enemyImageY;
	int BeatedMoveX;
	int count;
	int frameFromBeatTime;
	bool reverseFlag;
	bool isBeated;
	bool alive;
	int screen;
	DamageBeat* damageBeat;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
	std::shared_ptr<SnippetImage> snippetImage;
};


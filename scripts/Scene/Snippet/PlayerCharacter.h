#pragma once
#include <memory>
#include "Character.h"
#include "Enemy.h"
#include "Instrument.h"
#include "BeatManager.h"
#include "MessageWindow.h"
#include "EnemyManager.h"
#include "SnippetGameManager.h"
#include "SnippetSound.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(std::shared_ptr<SnippetGameManager> gameManager, std::shared_ptr<SnippetSound> ins);
	~PlayerCharacter() = default;
	bool update() override;
	void draw() const override;
	void setHP(int HP);
	void setPP(int PP);
	void setName(int charNum, int charSpriteNum);
	void setMyTurn(int Number);
	void setEnemyManagerInstance(EnemyManager* enemyManagerInstance);
	void setBeatManager(BeatManager* beatManagerInstance) { beatManager = beatManagerInstance; }
	void setMessageWindow(MessageWindow* messageInstance) { messageWindow = messageInstance; }
	void setCharacterId(int Number);
	void setInstrumentNumber(int Number);
	void setAlwaysActive(bool flag);
	void reverseCharacter();
	int scoreCheck();
	int scoreCheckSub();
	int getName(int charNum) const;
	int getHP() const;
	int getPP() const;
	int getNameLength() const;
	int getCharacterID() const { return characterID; }
	bool getIsActive() const { return (isActive || alwaysActive); }
	bool getReverseFlag() const { return reverseFlag; }
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
private:
	void playMainSoundNumberMem(int numberOfSound);
	void playSubSoundNumberMem(int numberOfSound);
	void reverseSub();
	bool isActive;
	bool alwaysActive;
	int myName[6];
	int myHP;
	int myPP;
	int myTurn;
	int nameLength;
	int mainSoundNumber;
	int subSoundNumber;
	int characterID;
	int damage;
	int turnDamage;
	int lastPlayedStep = -1;
	bool reverseFlag;
	EnemyManager* enemyManagerIns;
	Instrument* myInstrument;
	BeatManager* beatManager;
	MessageWindow* messageWindow;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetSound> snippetSound;
};


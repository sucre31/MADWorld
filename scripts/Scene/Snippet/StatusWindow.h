#pragma once

#include <memory>
#include "Common/GameObject/GameObject.h"
#include "PlayerCharacter.h"
#include "SnippetGameManager.h"
#include "SnippetImage.h"


class StatusWindow : GameObject
{
public:
	StatusWindow(std::shared_ptr<SnippetGameManager> managerIns, std::shared_ptr<SnippetImage> image);
	virtual ~StatusWindow() = default;
	bool update() override;
	void draw() const override;
	void setWindowPos(int No);
	void setPlayerCharacterInstance(PlayerCharacter* playerCharacterInstance);
	void setTargetHP(int hpChara);
	void setTargetPP(int ppChara);
	void setHP(int hpChara);
	void setPP(int ppChara);
	void setName();
	void addPlayerHP(int value);
	int getNameToSprite(int charNum) const;
	int getDumrollNum(int drumNum) const;
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	int hp, pp;			//戦闘中のHPは時間で小数点管理される、ここのHPを元にし、整数値になったらプレイヤーに返す
	int targetHP, targetPP;
	int myX, myY;		//ウィンドウのポジションを調整
	int myName[6];
	int myNameLength;
	int frameCount;
	bool damageShake;
	double shakeTime = 0.0;
	double shakeDuration = 0.5;   // 揺れる時間（秒）
	double shakeAmplitude = 9.0;  // 揺れ幅
	double shakeOffsetX = 0.0;
	void calcPoint();
	void drawHP(int drawX) const;
	void drawName(int drawX) const;
	//std::shared_ptr<PlayerCharacter> playerCharacter;
	PlayerCharacter* playerCharacter;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetImage> snippetImage;
};


#pragma once
#include <memory>
#include "System/Singleton.h"
#include "System/FpsControl.h"
#include "SnippetGameManager.h"

class SnippetGameManager
{
public:
	SnippetGameManager();
	~SnippetGameManager() = default;
	void nextTurn() { nextTurnFlag = true; }
	void minusTurn() { returnTurnFlag = true; }		//基本使わない
	int getTurn() { return TurnNum; };
	void setFrameChange(bool isChanged) {}
	void proceedTurn();
	void initBattle() { TurnNum = 0; }
	FpsControl* getFpsIns() { return FpsControl::getIns(); }
private:
	bool nextTurnFlag;
	bool returnTurnFlag;
	int TurnNum;	// リュカ、クマトラ、ダスター、ボニー
	std::shared_ptr<SnippetGameManager> snippetGameManager;
};


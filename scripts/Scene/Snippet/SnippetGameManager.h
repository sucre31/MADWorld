#pragma once
#include <memory>
#include "Singleton.h"
#include "FpsControl.h"
#include "SnippetGameManager.h"

class SnippetGameManager
{
public:
	SnippetGameManager();
	~SnippetGameManager() = default;
	void nextTurn() { nextTurnFlag = true; }
	void minusTurn() { returnTurnFlag = true; }		//Šî–{Žg‚í‚È‚¢
	int getTurn() { return TurnNum; };
	void setFrameChange(bool isChanged) {}
	void proceedTurn();
	void initBattle() { TurnNum = 0; }
	FpsControl* getFpsIns() { return FpsControl::getIns(); }
private:
	bool nextTurnFlag;
	bool returnTurnFlag;
	int TurnNum;
	FpsControl* fpsIns;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
};


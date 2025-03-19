#include "SnippetGameManager.h"

SnippetGameManager::SnippetGameManager() {
	nextTurnFlag = false;
	returnTurnFlag = false;
}


void SnippetGameManager::proceedTurn() {
	if (nextTurnFlag) {
		TurnNum++;
	}
	if (returnTurnFlag) {
		TurnNum--;
	}
	nextTurnFlag = false;
	returnTurnFlag = false;
}
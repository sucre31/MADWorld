#pragma once
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/PlayerCharacter.h"

class SetSoundAction : public IEventAction {
private:
	PlayerCharacter* player;
	int setNum;	// サウンドのセット番号を指定

public:
	SetSoundAction(PlayerCharacter* p, int num)
		: player(p), setNum(num) {
	}

	void execute() override {
		player->setSoundSet(setNum);
	}
};
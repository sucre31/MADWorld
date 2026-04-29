#pragma once
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/PlayerCharacter.h"

class SetActiveAction : public IEventAction {
private:
	PlayerCharacter* player;
	bool flag;

public:
	SetActiveAction(PlayerCharacter* p, bool f)
		: player(p), flag(f) {
	}

	void execute() override {
		player->setAlwaysActive(flag);
	}
};
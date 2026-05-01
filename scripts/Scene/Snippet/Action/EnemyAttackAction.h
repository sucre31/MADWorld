#pragma once
#include <string>
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/Enemy.h"

class EnemyAttackAction : public IEventAction
{
private:
	Enemy* enemy;
	bool attackFlash = false;
	int soundIndex = 0;
	int damage = 0;
	int targetPlayerId = 0;
public:
	EnemyAttackAction(Enemy* e, int sIndex, int damage, int targetId)
		: enemy(e), soundIndex(sIndex), damage(damage), targetPlayerId(targetId) {
	}

	EnemyAttackAction(Enemy* e, bool f)
		: enemy(e), attackFlash(f){
	}

	void execute() override;

};


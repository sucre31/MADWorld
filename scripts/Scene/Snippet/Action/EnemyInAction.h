#pragma once
#include <string>
#include <memory>
#include "Common/Event/IEventAction.h"
#include "Scene/Snippet/Enemy.h"

class EnemyInAction : public IEventAction
{
private:
	Enemy* enemy;
	MoveInDir dir;
public:
	EnemyInAction(Enemy* e, MoveInDir d)
		:enemy(e), dir(d) {
	}

	void execute() override;

};


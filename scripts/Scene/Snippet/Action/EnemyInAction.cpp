#include "EnemyInAction.h"

void EnemyInAction::execute() {
	enemy->playMoveIn(dir);
	enemy->setWait(false);
}
#include "EnemyAttackAction.h"

void EnemyAttackAction::execute() {
	if (attackFlash) {
		enemy->setAttackFlash(true);
	}
	else {
		enemy->setEnemySoundIndex(soundIndex);
		enemy->attack(targetPlayerId, damage);
	}
}
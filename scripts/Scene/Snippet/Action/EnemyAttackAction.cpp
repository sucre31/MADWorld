#include "EnemyAttackAction.h"

void EnemyAttackAction::execute() {
	if (attackFlash) {
		enemy->setAttackFlash(true);
	}
	else {
		if (damage < 0) {
			damage += GetRand(10) - 5;
		}
		enemy->setEnemySoundIndex(soundIndex);
		enemy->attack(targetPlayerId, damage);
	}
}
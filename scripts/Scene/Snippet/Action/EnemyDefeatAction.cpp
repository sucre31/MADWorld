#include "EnemyDefeatAction.h"

void EnemyDefeatAction::execute() {
	if (finalBossflag) {
		PlaySoundMem(snippetSound->getBattleSE()[5], DX_PLAYTYPE_BACK);
		enemy->setDeathType(DeathType::Boss);
		enemy->setAlive(false);
		enemy->setNextEnemyId(-1);
	}
	else {
		PlaySoundMem(snippetSound->getBattleSE()[3], DX_PLAYTYPE_BACK);
		enemy->setDeathType(DeathType::Normal);
		enemy->setAlive(false);
		enemy->setNextEnemyId(nextEnemyId);
	}
}
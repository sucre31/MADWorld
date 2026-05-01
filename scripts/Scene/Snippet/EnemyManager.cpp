#include <Dxlib.h>
#include "EnemyManager.h"
#include "StatusWindowManager.h"

EnemyManager::EnemyManager(
	std::shared_ptr<SnippetGameManager> managerIns,
	std::shared_ptr<SnippetImage> imgIns,
	std::shared_ptr<SnippetSound> sound,
	std::shared_ptr<PlayerCharacterManager> player,
	std::shared_ptr<StatusWindowManager> window
) {
	int i;
	snippetGameManager = managerIns;
	snippetSound = sound;
	snippetImage = imgIns;
	playerManager = player;
	statusManager = window;
	for (i = 0; i < NumberOfEnemy; i++) {
		if (i < 5) {
			enemy[i] = new Enemy(-120 + 60 * i, 0,snippetGameManager, snippetImage, snippetSound, playerManager, statusManager);
		}
		else {
			switch (i) {
			case 5:
				enemy[i] = new Enemy(-120, 50, snippetGameManager, snippetImage, snippetSound, playerManager, statusManager);
				enemy[i]->setNewEnemy(0);
				break;
			case 6:
				enemy[i] = new Enemy(0, -30, snippetGameManager, snippetImage, snippetSound, playerManager, statusManager);
				enemy[i]->setNewEnemy(0);
				break;
			case 7:
				enemy[i] = new Enemy(120, 50, snippetGameManager, snippetImage, snippetSound, playerManager, statusManager);
				enemy[i]->setNewEnemy(0);
				break;
			}
		}

	}
}

bool EnemyManager::update() {
	for (int i = 0; i < NumberOfEnemy; i++) {
		if (!enemy[i]->getAlive()) {
			if (enemy[i]->isDeadFinished()) {
				int nextId = enemy[i]->getNextEnemyId();
				if (nextId != -1) {
					enemy[i]->setNewEnemy(nextId % NumberOfKind);
				}
			}
		}
		enemy[i]->update();
	}
	return true;
}

void EnemyManager::draw() const {
	enemy[6]->draw();
	for (int i = 0; i < NumberOfEnemy; i++) {
		if (enemy[i] != nullptr && i != 6) {
			enemy[i]->draw();
		}
	}
}

Enemy* EnemyManager::getEnemyIns(int num) {
	if (num < NumberOfEnemy) {
		return enemy[num];
	}
	return nullptr;
}

void EnemyManager::drawSecond() const {
	for (int i = 0; i < NumberOfEnemy; i++) {
		enemy[i]->drawSecond();
	}
}
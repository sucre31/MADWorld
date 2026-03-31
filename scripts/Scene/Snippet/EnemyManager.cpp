#include <Dxlib.h>
#include "EnemyManager.h"

EnemyManager::EnemyManager() {
	int i;
	for (i = 0; i < NumberOfEnemy; i++) {
		if (i < 5) {
			enemy[i] = new Enemy(-120 + 60 * i, 0, snippetImage, snippetGameManager);
		}
		else {
			switch (i) {
			case 5:
				enemy[i] = new Enemy(-120, 50, snippetImage, snippetGameManager);
				enemy[i]->setNewEnemy(0);
				break;
			case 6:
				enemy[i] = new Enemy(0, -50, snippetImage, snippetGameManager);
				enemy[i]->setNewEnemy(0);
				break;
			case 7:
				enemy[i] = new Enemy(120, 50, snippetImage, snippetGameManager);
				enemy[i]->setNewEnemy(0);
				break;
			}
		}
		enemy[i]->SetSound(snippetSound);

	}
}

bool EnemyManager::update() {
	for (int i = 0; i < NumberOfEnemy; i++) {
		if (!enemy[i]->getAlive()) {
			WaitTimer(100);	//‘ã‘Ö‚·‚×‚«
			enemy[i]->setNewEnemy((enemy[i]->getID() + 1 + GetRand(NumberOfKind - 2)) % NumberOfKind);
		}
		enemy[i]->update();
	}
	return true;
}

void EnemyManager::draw() const {
	for (int i = 0; i < NumberOfEnemy; i++) {
		enemy[i]->draw();
	}
}

void EnemyManager::drawSecond() const {
	for (int i = 0; i < NumberOfEnemy; i++) {
		enemy[i]->drawSecond();
	}
}
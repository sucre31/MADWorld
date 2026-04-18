#include <Dxlib.h>
#include "EnemyManager.h"

EnemyManager::EnemyManager(std::shared_ptr<SnippetGameManager> managerIns, std::shared_ptr<SnippetImage> imgIns, std::shared_ptr<SnippetSound> sound) {
	int i;
	snippetGameManager = managerIns;
	snippetSound = sound;
	snippetImage = imgIns;
	for (i = 0; i < NumberOfEnemy; i++) {
		if (i < 5) {
			enemy[i] = new Enemy(-120 + 60 * i, 0,snippetGameManager, snippetImage, snippetSound);
		}
		else {
			switch (i) {
			case 5:
				enemy[i] = new Enemy(-120, 50, snippetGameManager, snippetImage, snippetSound);
				enemy[i]->setNewEnemy(0);
				break;
			case 6:
				enemy[i] = new Enemy(0, -30, snippetGameManager, snippetImage, snippetSound);
				enemy[i]->setNewEnemy(0);
				break;
			case 7:
				enemy[i] = new Enemy(120, 50, snippetGameManager, snippetImage, snippetSound);
				enemy[i]->setNewEnemy(0);
				break;
			}
		}

	}
}

bool EnemyManager::update() {
	for (int i = 0; i < NumberOfEnemy; i++) {
		if (!enemy[i]->getAlive()) {
			WaitTimer(100);	//代替すべき
			enemy[i]->setNewEnemy((enemy[i]->getID() + 1 + GetRand(NumberOfKind - 2)) % NumberOfKind);
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

void EnemyManager::drawSecond() const {
	for (int i = 0; i < NumberOfEnemy; i++) {
		enemy[i]->drawSecond();
	}
}
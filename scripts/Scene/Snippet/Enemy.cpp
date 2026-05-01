#include <Dxlib.h>
#include "Enemy.h"
#include "Common/Image.h"
#include "System/Pad.h"
#include "System/Define.h"
#include "Common/Sound.h"
#include "SnippetGameManager.h"
#include "PlayerCharacterManager.h"
#include "StatusWindowManager.h"
#include "StatusWindow.h"

Enemy::Enemy(
	int x, int y,
	std::shared_ptr<SnippetGameManager> gameManager,
	std::shared_ptr<SnippetImage> image,
	std::shared_ptr<SnippetSound> sound,
	std::shared_ptr<PlayerCharacterManager> player,
	std::shared_ptr<StatusWindowManager> window
) : myX(x),
	myY(y),
	HP(1000),
	myID(0),
	alive(true),
	count(0),
	BeatedMoveX(0),
	reverseFlag(false),
	isBeated(false),
	damageBeat(std::make_unique<DamageBeat>()),
	playerManager(player),
	statusManager(window)
{
	SetGameManager(gameManager);
	SetImage(image);
	SetSound(sound);

	attackFlash = false;

	damageBeat->SetGameManager(gameManager);
	damageBeat->SetImage(image);


	getSize();
	screen = MakeScreen(enemyImageX, enemyImageY, TRUE);
}

bool Enemy::update() {

	double dt = snippetGameManager->getFpsIns()->getDeltaTime();

	if (attackFlash) {
		attackFlashTime += dt;

		if (attackFlashTime >= attackFlashDuration) {
			attackFlash = false;
			attackFlashTime = 0.0;
		}
	}

	if (!alive) {
		deadTime += dt;
	}
	else {
		deadTime = 0.0; // 復活時リセット（念のため）
	}

	if (isBeated) {
		if (snippetGameManager->getFpsIns()->isFrameChanged()) {
			BeatedMoveX = (int)(5 * sin(Define::PI * (frameFromBeatTime / 4.0)));

			if (frameFromBeatTime == 16) {
				BeatedMoveX = 0;
				isBeated = false;
				frameFromBeatTime = 0;
			}
			else {
				frameFromBeatTime++;
			}
		}
	}

	if (moveAnimActive) {

		double dt = snippetGameManager->getFpsIns()->getDeltaTime();
		moveAnimTime += dt;

		double t = moveAnimTime / moveAnimDuration;

		if (t >= 1.0) {
			moveAnimActive = false;
			moveOffsetX = 0;
			moveOffsetY = 0;
		}
		else {
			double ease = 1.0 - (1.0 - t) * (1.0 - t);

			float distance = 80.0f * (1.0f - ease);

			switch (moveDir) {
			case MoveInDir::Left:
				moveOffsetX = -distance;
				break;

			case MoveInDir::Right:
				moveOffsetX = distance;
				break;

			case MoveInDir::Up:
				moveOffsetY = -distance;
				break;

			case MoveInDir::Down:
				moveOffsetY = distance;
				break;
			}
		}
	}

	// 一旦HPは無視(EnemyDefeatActionで管理)
	//if (HP < 0 && alive) {
	//	alive = false;
	//	PlaySoundMem(snippetSound->getBattleSE()[3], DX_PLAYTYPE_BACK);
	//}
	damageBeat->update();
	return true;
}

void Enemy::setDeathType(DeathType type) {
	deathType = type;

	switch (deathType) {
	case DeathType::Normal:
		deadDuration = 0.4;
		break;

	case DeathType::Boss:
		deadDuration = 2.5;
		break;
	}
}

void Enemy::setAttackFlash(bool attack) {
	PlaySoundMem(snippetSound->getBattleSE()[6], DX_PLAYTYPE_BACK);
	attackFlashTime = 0;
	attackFlash = attack;
}

void Enemy::attack(int targetId, int damage) {
	if (damage == 10) {
		// とりあえずダメージ10 = sleep であつかう(よくないけど)
		statusManager->getWindowById(targetId)->setSleep(true);
		return;
	}
	else if (damage == 9) {
		// ダメージ9 = 揺れにする(よくない)
		statusManager->getWindowById(0)->setSleepShake(true);
		statusManager->getWindowById(1)->setSleepShake(true);
		statusManager->getWindowById(2)->setSleepShake(true);
		statusManager->getWindowById(3)->setSleepShake(true);
		PlaySoundMem(snippetSound->getEnemySE()[attackSoundHandleIndex], DX_PLAYTYPE_BACK);
		return;
	}

	if (damage < 0) {
		PlaySoundMem(snippetSound->getBattleSE()[4], DX_PLAYTYPE_BACK);
	}
	PlaySoundMem(snippetSound->getEnemySE()[attackSoundHandleIndex], DX_PLAYTYPE_BACK);
	statusManager->getWindowById(targetId)->addPlayerHP(damage);
}

void Enemy::draw() const {
	if ((!alive && deadTime >= deadDuration )|| wait) {
		return; // 何も描かない
	}

	if (!alive) {
		double t = deadTime / deadDuration; // 0〜1

		SetDrawScreen(screen);
		ClearDrawScreen();

		DrawGraph(0, 0, snippetImage->getEnemyImage()[myID], TRUE);

		if (t < 0.5) {
			// 白飛び
			double phase = t / 0.5;

			double wave = sin(phase * Define::PI);
			double eased = wave * wave;

			int alpha = (int)(eased * 255);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawGraph(0, 0, snippetImage->getEnemyImage()[myID], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			// 暗くする
			double phase = (t - 0.5) / 0.5;

			int alpha = (int)(phase * 255);

			SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);
			DrawGraph(0, 0, snippetImage->getEnemyImage()[myID], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		SetDrawScreen(snippetImage->getScreenHandle());

		DrawRotaGraph(
			160 + myX + BeatedMoveX,
			90 + myY,
			1.0,
			0,
			screen,
			TRUE,
			reverseFlag
		);
	}
	else {
		SetDrawScreen(screen);
		ClearDrawScreen();

		DrawGraph(0, 0, snippetImage->getEnemyImage()[myID], TRUE);

		// フラッシュ
		if (attackFlash) {
			double t = attackFlashTime / attackFlashDuration;

			double cycle = 2.0;
			double wave = fabs(sin(t * cycle * Define::PI)); // 0〜1

			int alpha = (int)(wave * 180);

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

			DrawGraph(0, 0, snippetImage->getEnemyImage()[myID], TRUE);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		SetDrawScreen(snippetImage->getScreenHandle());

		DrawRotaGraph(
			160 + myX + BeatedMoveX + (int)moveOffsetX,
			90 + myY + (int)moveOffsetY,
			1.0,
			0,
			screen,
			TRUE,
			reverseFlag
		);
	}
}

void Enemy::drawSecond() const {
	damageBeat->draw();
}

void Enemy::getSize() {
	if (snippetImage->getEnemyImage()[myID] != -1) {
		GetGraphSize(snippetImage->getEnemyImage()[myID], &enemyImageX, &enemyImageY);
	}
	else {
		enemyImageX = 1;
		enemyImageY = 1;
	}
}

void Enemy::setEnemySoundIndex(int soundIndex) {
	attackSoundHandleIndex = soundIndex;
}

void Enemy::setAlive(bool flag) {
	alive = flag;
}

void Enemy::playMoveIn(MoveInDir dir)
{
	moveDir = dir;
	moveAnimActive = true;
	moveAnimTime = 0.0;

	moveOffsetX = 0.0f;
	moveOffsetY = 0.0f;
}

void Enemy::setNewEnemy(int EnemyID) {
	myID = EnemyID;
	HP = 1000;
	alive = true;
	DeleteGraph(screen);
	getSize();
	screen = MakeScreen(enemyImageX, enemyImageY, TRUE);
}

void Enemy::getDamage(int valueOfDamage, bool isEarly) {
	reverseFlag = !reverseFlag;
	HP -= valueOfDamage;
	isBeated = true;
	frameFromBeatTime = 0;
	damageBeat->addDamage(valueOfDamage, isEarly, myX, myY);
}


#include <Dxlib.h>

#include "PlayerCharacter.h"
#include "System/Pad.h"
#include "Common/Sound.h"
#include "EnemyManager.h"

PlayerCharacter::PlayerCharacter(std::shared_ptr<SnippetGameManager> gameManager, std::shared_ptr<SnippetSound> soundIns, std::shared_ptr<PopupNumberManager> pManager) {
	mainSoundNumber = 0;
	subSoundNumber = 0;
	snippetGameManager = gameManager;
	snippetSound = soundIns;
	popupManager = pManager;
	myInstrument = new Instrument(snippetSound);
	//myInstrument->setBeatManager(beatManager);
	reverseFlag = FALSE;
	alwaysActive = false;
	damage = 0;
}

bool PlayerCharacter::update() {
	if (snippetGameManager->getTurn() % 4 == myTurn) {
		isActive = true;
		scoreCheck();
		if (Pad::getIns()->get(ePad::up) >= 1) {
			myHP++;
		}
		if (Pad::getIns()->get(ePad::down) >= 1) {
			myHP--;
		}

		if (Pad::getIns()->get(ePad::A) == 1) {
			playMainSoundNumberMem(mainSoundNumber);
			reverseCharacter();
			damage = scoreCheck();
			turnDamage += damage;
			if (damage >= 86) PlaySoundMem(snippetSound->getBattleSE()[2], DX_PLAYTYPE_BACK);
			enemyManagerIns->getEnemyIns(2)->getDamage(damage, beatManager->isEarly());
			mainSoundNumber++;
			if (mainSoundNumber % 12 == 6 && characterID == 0) mainSoundNumber = 8;
		}
		if (Pad::getIns()->get(ePad::left) == 1) {
			playSubSoundNumberMem(subSoundNumber);
			setPP(subSoundNumber);
			reverseCharacter();
			damage = scoreCheckSub();
			reverseSub();
			subSoundNumber++;
		}
		if (Pad::getIns()->get(ePad::R) == 1) {
			snippetGameManager->nextTurn();
			PlaySoundMem(snippetSound->getBattleSE()[1], DX_PLAYTYPE_BACK);
			isActive = false;
		}
		if (Pad::getIns()->get(ePad::ZR) == 1) {
			alwaysActive = !alwaysActive;
		}

		if (beatManager->isStepChanged() && Pad::getIns()->get(ePad::L) >= 1) {
			myInstrument->playWithStep(beatManager->getNumberOfStep(), 0);
			myInstrument->playWithStep(beatManager->getNumberOfStep(), 0);
			if (myInstrument->playWithStep(beatManager->getNumberOfStep(), 1)) {
				damage = scoreCheck();
				if (damage >= 86) PlaySoundMem(snippetSound->getBattleSE()[2], DX_PLAYTYPE_BACK);
				enemyManagerIns->getEnemyIns(2)->getDamage(damage, beatManager->isEarly());
			}
		}
		if (myHP < 0) {
			myHP = 0;
		}
	}
	else if (alwaysActive) {
		int step = beatManager->getNumberOfStep();

		if (step != lastPlayedStep) {
			if (myInstrument->playWithStep(step, 0)) {
				enemyManagerIns->getEnemyIns(targetEnemy)->getDamage(damage, beatManager->isEarly());
			}
			lastPlayedStep = step;
		}
	}
	return true;
}

void PlayerCharacter::setAlwaysActive(bool flag) {
	alwaysActive = flag;
}

void PlayerCharacter::setTargetEnemy(int target) {
	targetEnemy = target;
}

void PlayerCharacter::draw() const {
}

void PlayerCharacter::reverseCharacter() {
	reverseFlag = !reverseFlag;
}

/*!
@brief 現在のターゲットになるステップ数を計算したうえでポイントをもらう
*/
int PlayerCharacter::scoreCheck() {
	int targetStep;
	int addNumber = 0, addValue = 0;
	bool isTargetDecide = false;
	targetStep = beatManager->getNumberOfStep();
	isTargetDecide = myInstrument->playWithStep(targetStep, 1);
	while (!isTargetDecide) {
		if (addNumber % 2 == 0) {
			addValue = (int)(addNumber / 2 + 1);
		}
		else {
			addValue = -(int)(addNumber / 2 + 1);
		}
		isTargetDecide = myInstrument->playWithStep(targetStep + addValue, 1);
		addNumber++;
		if (addNumber == 128) break;
	}

	return beatManager->checkNowScore(targetStep + addValue);
}

/*!
@brief 現在のターゲットになるステップ数を計算したうえでポイントをもらう(サブ音源用)
*/
int PlayerCharacter::scoreCheckSub() {
	int targetStep;
	int addNumber = 0, addValue = 0;
	bool isTargetDecide = false;
	targetStep = beatManager->getNumberOfStep();
	isTargetDecide = myInstrument->playWithStep(targetStep, 2);
	while (!isTargetDecide) {
		if (addNumber % 2 == 0) {
			addValue = (int)(addNumber / 2 + 1);
		}
		else {
			addValue = -(int)(addNumber / 2 + 1);
		}
		isTargetDecide = myInstrument->playWithStep(targetStep + addValue, 2);
		addNumber++;
		if (addNumber == 128) break;
	}

	return beatManager->checkNowScore(targetStep + addValue);
}


/*!
@brief キャラクターのHPを設定
*/
void PlayerCharacter::setHP(int HP) {
	myHP = HP;
}

/*!
@brief キャラクターのHPの増減
*/
void PlayerCharacter::addHP(int value) {
	myHP += value;
	if (myHP < 0) {
		myHP = 0;
	}
}

void PlayerCharacter::setPopupNumber(int value, int x, int y) {
	if (value < 0) {
		popupManager->add(-value, x, y);
	}
}


/*
@brief キャラクターのPPを設定
*/
void PlayerCharacter::setPP(int PP) {
	myPP = PP;
}

/*
@brief キャラクターの名前を設定
@param charNum 文字数
@param charSpriteNum スプライト番号
*/
void PlayerCharacter::setName(int charNum, int charSpriteNum) {
	myName[charNum] = charSpriteNum;
	nameLength = charNum + 1;
}

/*
@brief キャラクターの行動ターンを設定
@param charNum 文字数
*/
void PlayerCharacter::setMyTurn(int Number) {
	myTurn = Number;
}

void PlayerCharacter::setInstrumentNumber(int Number) {
	myInstrument->setMyInstrumentNumber(Number);
}

/*!
@brief 敵のインスタンスを取得
@param charNum 何体目?
@param enemyInstance 敵のインスタンス
*/
void PlayerCharacter::setEnemyManagerInstance(EnemyManager* enemyInstance) {
	enemyManagerIns = enemyInstance;
}

void PlayerCharacter::setCharacterId(int Number) {
	characterID = Number;
}

/*!
@brief キャラクターの名前を取得
@param charNum 何文字目？
*/
int PlayerCharacter::getName(int charNum) const {
	if (charNum < 6 && charNum >= 0) {
		return myName[charNum];
	}
	else {
		return 0;
	}
}

/*!
@brief キャラクターの名前を取得
@param charNum 何文字目？
*/
int PlayerCharacter::getNameLength() const {
	return nameLength;
}

/*!
@brief キャラクターのHPを取得
*/
int PlayerCharacter::getHP() const {
	return myHP;
}

/*!
@brief キャラクターのPPを取得
*/
int PlayerCharacter::getPP() const {
	return myPP;
}

/*!
@brief メインの音を順番に並べる
*/
void PlayerCharacter::playMainSoundNumberMem(int numberOfSound) {
	myInstrument->playMainInstrument(numberOfSound);
}

void PlayerCharacter::playSubSoundNumberMem(int numberOfSound) {
	myInstrument->playSubInstrument(numberOfSound);
}

void PlayerCharacter::reverseSub() {
	switch (subSoundNumber % 4) {
	case 0:
		enemyManagerIns->getEnemyIns(0)->getDamage(damage, beatManager->isEarly());
		break;
	case 1:
		enemyManagerIns->getEnemyIns(1)->getDamage(damage, beatManager->isEarly());
		break;
	case 2:
		enemyManagerIns->getEnemyIns(3)->getDamage(damage, beatManager->isEarly());
		break;
	case 3:
		enemyManagerIns->getEnemyIns(4)->getDamage(damage, beatManager->isEarly());
		break;
	}
}

///*!
//@brief 引数に対応した音(メイン)をならす
//@param numberOfSound BPMに対応した音の番号 128でループ
//*/
//void playSoundNumberAMem(int numberOfBPM) {
//	int switchNumber = 0;
//	numberOfBPM = numberOfBPM % 128
//	if (numberOfBPM < 16) {
//		switchNumber = 0;
//	}
//	else if (numberOfBPM < 24) {
//		switchNumber = 1;
//	}
//	else if (numberOfBPM < 32) {
//		switchNumber = 2;
//	}
//	else if (numberOfBPM < 48) {
//		switchNumber = 0;
//	}
//	else if (numberOfBPM < 56) {
//		switchNumber = 1;
//	}
//	else if (numberOfBPM < 64) {
//		switchNumber = 2;
//	}
//	else if (numberOfBPM < 80) {
//		switchNumber = 4;
//	}
//	else if (numberOfBPM < 88) {
//		switchNumber = 5;
//	}
//	else if (numberOfBPM < 96) {
//		switchNumber = 6;
//	}
//	else if (numberOfBPM < 128) {
//		switchNumber = 6;
//	}
//
//	switch (numberOfBPM) {
//	default:
//		break;
//	case 0:
//		PlaySoundMem(Sound::getIns()->getLucasBattleSounds()[numberOfBPM], DX_PLAYTYPE_BACK);
//		break;
//	}
//}
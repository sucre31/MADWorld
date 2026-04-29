#include <Dxlib.h>
#include "BeatManager.h"
#include "Common/Sound.h"


BeatManager::BeatManager() {
	bpm = 165;
	startTime = GetNowHiPerformanceCount();
	deleyTime = (int)((60000 / bpm / 4) / 2);
	targetTime = 0;
	stepChangeFlag = false;
	numberOfStep = -1;
	currentScore = 1;
}

bool BeatManager::update() {
	int tmpStep;
	nowTime = GetNowHiPerformanceCount();
	double stepTime = 60000.0 / bpm / 4;
	tmpStep = (int)(((nowTime - startTime) / 1000.0) / stepTime);
	if (numberOfStep != tmpStep) {
		stepChangeFlag = true;
		numberOfStep = tmpStep;
	}
	else {
		stepChangeFlag = false;
	}
	checkNowScore(numberOfStep);

	return true;
}

void BeatManager::draw() const {
	if (isBeatEarly) {
		DrawFormatString(40 + currentScore, 10, GetColor(255, 255, 0), "%d", currentScore);
	}
	else {
		DrawFormatString(40 + currentScore, 10, GetColor(0, 255, 255), "%d", currentScore);
	}
}

void BeatManager::startMusic(int musicNumber) {
	if (musicNumber < 2) PlaySoundMem(snippetSound->getBackgroundMusic()[musicNumber], DX_PLAYTYPE_BACK);
	startTime = GetNowHiPerformanceCount();
}

/*!
@brief　目的のステップと現在の時間との差から点数(ダメージ)を算出
@param targetStep 判定するステップ
*/
int BeatManager::checkNowScore(int targetStep) {
	int tmpScore;
	targetTime = ((int)((60000 / bpm / 4) * targetStep));
	tmpScore = ((nowTime - startTime) / 1000) - targetTime;
	if (abs(tmpScore) < (deleyTime * 8)) {
		currentScore = 80 - 40 * log10(fabs(tmpScore) + 1) + (GetRand(20) - 10);;
		if (tmpScore < 0) {
			isBeatEarly = true;
		}
		else {
			isBeatEarly = false;
		}
		if (currentScore < 0) currentScore = 1;
		return currentScore;
	}
	currentScore = -30;
	return -1;
}
#include "BPMManager.h"

BPMManager::BPMManager() {
	bpm = 1.0;
	beatTime = 60000000.0 / bpm;
	BGMStartTime = GetNowHiPerformanceCount();
}

void BPMManager::startMusic() {
	BGMStartTime = GetNowHiPerformanceCount();
}

double BPMManager::getCurrentBeatNum() {
	LONGLONG nowTime = GetNowHiPerformanceCount();
	return (nowTime - BGMStartTime) / beatTime;
}

/*
@brief 拍数を入れると時間を返す
*/
LONGLONG BPMManager::getTargetBeatTime(double beatNum) {
	return BGMStartTime + (LONGLONG)(beatTime * beatNum);
}

void BPMManager::setBPM(double beatPM) {
	bpm = beatPM;
	beatTime = 60000000.0 / bpm;
}
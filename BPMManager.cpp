#include "BPMManager.h"

BPMManager::BPMManager() {
	bpm = 1;
	BGMStartTime = GetNowHiPerformanceCount();
}

void BPMManager::startMusic() {
	BGMStartTime = GetNowHiPerformanceCount();
}

double BPMManager::getCurrentBeatNum() {
	LONGLONG nowTime = GetNowHiPerformanceCount();
	return (nowTime - BGMStartTime) / ((60000000 / bpm));
}

/*
@brief 拍数を入れると時間を返す
*/
LONGLONG BPMManager::getTargetBeatTime(double beatNum) {
	LONGLONG time;
	time = BGMStartTime + (60000000 / bpm) * beatNum;
	return time;
}
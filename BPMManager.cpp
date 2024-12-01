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
@brief ����������Ǝ��Ԃ�Ԃ�
*/
LONGLONG BPMManager::getTargetBeatTime(double beatNum) {
	LONGLONG time;
	time = BGMStartTime + (60000000 / bpm) * beatNum;
	return time;
}
#include "BPMManager.h"

BPMManager::BPMManager() {
	bpm = 1.0;
	beatTime = 60000000.0 / bpm;
}

void BPMManager::startMusic(int handle) {
	bgmHandle = handle;
}

double BPMManager::getCurrentBeatNum() {
	if (bgmHandle == -1) return 0.0;

	double currentMs = GetSoundCurrentTime(bgmHandle);
	return currentMs / (60000.0 / bpm);
}

/*
@brief 拍数を入れると時間を返す
*/
double BPMManager::getTargetBeatTime(double beatNum) {
    return beatNum * (60000.0 / bpm);
}

void BPMManager::setBPM(double beatPM) {
	bpm = beatPM;
	beatTime = 60000000.0 / bpm;
}
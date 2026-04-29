#pragma once
#include <Dxlib.h>
// BPMを所得して，開始時間、小節数などを管理
class BPMManager
{
public:
	BPMManager();
	~BPMManager() = default;
	void setBPM(double beatPM);
	void startMusic(int handle);
	double getCurrentBeatNum();
	double getTargetBeatTime(double);
	LONGLONG getOneBeatTime() { return (LONGLONG)60000000 / bpm; }
private:
	int bgmHandle = -1;
	double bpm;
	double beatTime; // 1拍の時間
};


#pragma once
#include <Dxlib.h>
// BPMを所得して，開始時間、小節数などを管理
class BPMManager
{
public:
	BPMManager();
	~BPMManager() = default;
	void setBpm(double beatPM) { bpm = beatPM; }
	void startMusic();
	double getCurrentBeatNum();
	LONGLONG getTargetBeatTime(double);
private:
	double bpm;
	LONGLONG BGMStartTime;

};


#pragma once
#include <Dxlib.h>
// BPM���������āC�J�n���ԁA���ߐ��Ȃǂ��Ǘ�
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


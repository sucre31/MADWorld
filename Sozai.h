#pragma once
#include "GameObject.h"
#include "Pad.h"

class Sozai : public GameObject
{
public:
	Sozai();
	~Sozai() {};
	void setMyId(int id) { myId = id; }
	bool update() override;
	void draw() const override;
	void setPosX(int xVal) { x = xVal; }
	void setPosY(int yVal) { y = yVal; }
	void setExRate(double val) { exRate = val; }
	void setSampleMovie(const char* fileName);
	void setSampleSound(const char * fileName);
	void playSample(int, bool);
	void setTriggerPad(int padEnum, int indexNum);
	void setTriggerMidi(int midiEnum, int indexNum);
	int getTriggerPad(int num) { return triggerPad[num]; };
	int getTriggerMidi(int num) { return triggerMidi[num]; };
	int getValidPadNum() { return validPadNum; }
	int getValidMidiNum() { return validMidiNum; }
	int getPadSoundIndex(int num) { return padSoundIndex[num]; }
	int getMidiSoundIndex(int num) { return midiSoundIndex[num]; }
	void setMultiSound(bool flag) { enableMultiSound = flag; }
	void setIsDrum(bool flag) { isDrum = flag; }
	void setPadReleaseStop(bool flag) { enablePadPlayStop = flag; }
private:
	static const int maxSozai = 88;
	static const int maxPadSozai = 16;
	static const int maxMidiSozai = 88;
	int myId;								// managerクラスの管理番号
	int x;
	int y;
	int transX;
	int transY;
	double exRate;
	int myGrapghHandle;
	int mySoundHandle[maxSozai];
	bool enableTurn;
	bool turnFlag;
	int validSoundNum;
	int curSoundIndex;						// 再生中の音ハンドル
	int numOfPlayingSound;					// 再生中の音の数
	int triggerPad[maxPadSozai];			// 動的に作った方が良いなぁ あとクラス分けるべきかも
	int padSoundIndex[maxPadSozai];
	bool isPadSoundPlay[maxMidiSozai];
	int validPadNum;
	int triggerMidi[maxMidiSozai];
	int midiSoundIndex[maxMidiSozai];
	bool isMidiSoundPlay[maxMidiSozai];
	int validMidiNum;
	bool enableMultiSound;
	int prevTime;
	bool isDrum;							// 再生を止めなくする
	bool enablePadPlayStop;					// キーから指を離しても再生停止
};


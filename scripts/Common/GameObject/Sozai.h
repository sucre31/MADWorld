#pragma once
#include <vector>
#include "GameObject.h"
#include "System/Pad.h"
#include "Common/MovieImageWrapper.h"

class Sozai : public GameObject
{
public:
	Sozai();
	~Sozai();
	void setMyId(int id) { myId = id; }
	int getMyId() { return myId; }

	bool update() override;
	void draw() const override;

	void setPosX(double xVal) { x = xVal; }
	void setPosY(double yVal) { y = yVal; }

	void setLayer(int val);
	int getLayer() const;

	void setExRate(double val) { exRate = val; }

	void addSprite(const char* fileName);
	void addSprite(int soundIndex, const char* fileName);

	void setSampleSound(const char* fileName);

	void playSample(int, bool);
	void playWithSoundIndex(int);

	void stopSound();

	void setTriggerPad(int padEnum, int indexNum);
	void setTriggerMidi(int midiEnum, int indexNum);
	void setTriggerMidi(int midiEnum, int midiChannel, int soundIndexNum);

	void resetTriggerPad();

	int getTriggerPad(int num) { return triggerPad[num]; };
	int getTriggerMidiNote(int num) { return triggerMidiNote[num]; };
	int getTriggerMidiChannel(int index) const { return triggerMidiChannel[index]; }

	int getValidPadNum() { return triggerPad.size(); }
	int getValidMidiNum() { return validMidiNum; }

	int getPadSoundIndex(int num) { return padSoundIndex[num]; }
	int getMidiSoundIndex(int num) { return midiSoundIndex[num]; }

	double getPosX() { return x; }
	double getPosY() { return y; }

	void setMultiSound(bool flag) { enableMultiSound = flag; }
	void setMultiGraph(bool flag) { enableMultiGraph = flag; }

	void setIsDrum(bool flag) { isDrum = flag; }

	void setPadReleaseStop(bool flag) { enablePadPlayStop = flag; }

	void setUseTurn(bool flag) { enableTurn = flag; }

	void setPlayRate(int rate) { playRate = rate; }

	void setEnableMultiMovie(bool flag) { enableMultiSprite = flag; }

	void setGroupId(int id) { groupId = id; }
	int getGroupId() const { return groupId; }

	int getSoundCount() const { return validSoundNum; }

	void updatePlayingSoundCount();

private:

	static const int maxSozai = 128;
	static const int maxMidiSozai = 128;

	int layer = 0;

	int myId;

	double x;
	double y;

	int transX;
	int transY;

	double exRate;

	// soundIndex -> frames
	std::vector<std::vector<int>> graphHandles;

	int soundHandles[maxSozai];

	bool enableTurn;
	bool turnFlag;

	int validSoundNum;
	int curSoundIndex;
	int numOfPlayingSound;

	std::vector<int> triggerPad;
	std::vector<int> padSoundIndex;

	bool isPadSoundPlay[maxMidiSozai];

	int triggerMidiNote[maxMidiSozai];
	int triggerMidiChannel[maxMidiSozai];
	int midiSoundIndex[maxMidiSozai];

	bool isMidiSoundPlay[maxMidiSozai];

	int validMidiNum;

	bool enableMultiSound;
	bool enableMultiGraph;

	int prevTime;

	bool isDrum;

	bool enablePadPlayStop;

	std::vector<int> timeForAnime;
	std::vector<int> curGraphNum;
	std::vector<int> animeSoundIndex;

	int playRate;

	bool enableMultiSprite;

	int groupId = -1;

	MovieImageWrapper* movieWrapper;
};
#pragma once
#include "Common/GameObject/GameObject.h"
#include "Common/GameObject/Sozai.h"
#include "System/MIDI.h"

class SozaiManager : GameObject
{
public:
	SozaiManager();
	~SozaiManager() = default;
	bool update() override;
	void draw() const override;
	int makeSozai(const char * soundFileName, const char * imageFileName);
	int makeSozai(const char* soundFileName, const char* imageFileName, int x, int y);
	void playSozai(int, int);
	void stopSozai(int);
	void setSozaiKey(int sozaiNum, int padNum, int soundIndex);
	void resetSozaiKey(int sozaiNum);
	void setSozaiMidiKey(int sozaiNum, int midiNum, int soundIndex, int channel = 0);
	void setSozaiEx(int sozaiNum, double val);
	void setSozaiPos(int sozaiNum, int valX, int valY);
	void addSound(int sozaiNum, const char* soundFileName);
	void addSprites(int sozaiNum, const char* soundFileName);
	void changeTopLayer(int sozaiId);
	void setMultiSound(int sozaiId, bool flag);
	void setMultiGraph(int sozaiId, bool flag);
	void setDrumFlag(int, bool);
	void setPadReleaseStop(int, bool);
	void setReverseFlag(int, bool);
	void setPlayRate(int, int);
	void changePos(int , double valX, double valY);
	void drawSozai(int) const;
	void setGroupId(int sozaiNum, int groupId);
	int getSoundCount(int sozaiNum) const;
	int getSozaiCount() const { return sozai.size(); }
private:
	int validSozaiNum;
	std::vector<Sozai*> sozai; // shared_ptrにする
	std::vector<int> SozaiLayerIndex; // 更新順を保持する
};


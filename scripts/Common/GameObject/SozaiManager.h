#pragma once
#include "Sozai.h"
#include "MIDI.h"

class SozaiManager : GameObject
{
public:
	SozaiManager();
	~SozaiManager() = default;
	bool update() override;
	void draw() const override;
	void makeSozai(const char * soundFileName, const char * imageFileName);
	void makeSozai(const char* soundFileName, const char* imageFileName, int x, int y);
	void playSozai(int, int);
	void stopSozai(int);
	void setSozaiKey(int sozaiNum, int padNum, int soundIndex);
	void resetSozaiKey(int sozaiNum);
	void setSozaiMidiKey(int sozaiNum, int padNum, int soundIndex);
	void setSozaiEx(int sozaiNum, double val);
	void setSozaiPos(int sozaiNum, int valX, int valY);
	void addSound(int sozaiNum, const char* soundFileName);
	void addSprites(int sozaiNum, const char* soundFileName);
	void changeTopLayer(int sozaiId);
	void setMultiSound(int sozaiId, bool flag);
	void setMultiGraph(int sozaiId, bool flag);
	void setDrumFlag(int, bool);
	void setPadReleaseStop(int, bool);
	void setMovieFlag(int, bool);
	void setReverseFlag(int, bool);
	void setPlayRate(int, int);
	void changePos(int , double valX, double valY);
	void drawSozai(int) const;
	void setGroupId(int sozaiNum, int groupId);
private:
	int validSozaiNum;
	std::vector<Sozai*> sozai; // shared_ptrÇ…Ç∑ÇÈ
	std::vector<int> SozaiLayerIndex; // çXêVèáÇï€éùÇ∑ÇÈ
};


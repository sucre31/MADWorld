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
	void setSozaiKey(int sozaiNum, int padNum);
	void setSozaiMidiKey(int sozaiNum, int padNum);
	void setSozaiEx(int sozaiNum, double val);
	void setSozaiPos(int sozaiNum, int valX, int valY);
	void changeTopLayer(int sozaiId);
private:
	static const int limitOfSozai = 16;
	int validSozaiNum;
	Sozai* sozai[limitOfSozai]; // shared_ptr‚É‚·‚é
	int SozaiLayerIndex[limitOfSozai]; // XV‡‚ğ•Û‚·‚é
};


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
	void setSozaiKey(int sozaiNum, int padNum, int soundIndex);
	void setSozaiMidiKey(int sozaiNum, int padNum, int soundIndex);
	void setSozaiEx(int sozaiNum, double val);
	void setSozaiPos(int sozaiNum, int valX, int valY);
	void addSound(int sozaiNum, const char* soundFileName);
	void changeTopLayer(int sozaiId);
	void setMultiSound(int sozaiId, bool flag);
private:
	static const int limitOfSozai = 16;
	int validSozaiNum;
	Sozai* sozai[limitOfSozai]; // shared_ptr�ɂ���
	int SozaiLayerIndex[limitOfSozai]; // �X�V����ێ�����
};


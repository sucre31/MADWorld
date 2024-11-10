#pragma once
#include "Sozai.h"

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
	void changeTopLayer(int sozaiId);
private:
	static const int limitOfSozai = 16;
	int validSozaiNum;
	Sozai* sozai[limitOfSozai]; // shared_ptr�ɂ���
	int SozaiLayerIndex[limitOfSozai]; // �X�V����ێ�����
};

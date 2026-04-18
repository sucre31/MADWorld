#pragma once
#include "Common/SozaiBase.h"
//#include "Common/Online/HttpClient.h"
#include "Common/Online/WSClient.h"
#include "System/Define.h"


enum class ShuzoSozai
{
	Shuzo,
	ShuzoHeatL,
	ShuzoHeatR,
	ShuzoHeatMaskL,
	ShuzoHeatMaskR,
};

enum class ShuzoSound
{
	Shizukada
};

class SozaiShuzo : public SozaiBase
{
public:
	SozaiShuzo();
	void update() override;
	void draw() const override;
	~SozaiShuzo() = default;
	void initSozai() override;
	void shoutPlay();
private:
	WSClient ws;
	void setKey() override;
	void setLayerFront() override;
	void initializeFont();
	int fontHandle;
	const int shoutMax = 3;

	const int heatLeftPosX = 80;
	const int heatRightPosX = (Define::WIN_W - 80);
	const int heatBasePosY = Define::WIN_H / 2.0;
	const int heatMaxPosY = Define::WIN_H / 2.0 - 720;
	int shoutCount = 0;

	int timer;
	int prevVote = 0;

	float heatRatio = 0.0; // 会場の熱量
	float visualHeatRatio = 0.0f;
	float heatThreshold = 0.6;

	int tmpLagTimer;
	bool wsConnection = false;
};


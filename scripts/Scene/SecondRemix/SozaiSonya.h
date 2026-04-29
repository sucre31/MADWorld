#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "Common/GameObject/SozaiManager.h"
#include "Scene/Sonya/snowBall.h"
#include "System/Define.h"
#include "Common/SozaiBase.h"
#include "Scene/Sonya/sideBlank.h"

enum class SonyaSozai
{
	Sonya,
	Yasuna,
	Back0,
	Back1,
	Back2,
	Back3,
	Back4,
	Back5,
	Back6,
	OP
};

enum class SonyaSound
{
	Hey,
	Sukiari,
	SonyaChan,
	Tto,
	Hit
};

class SozaiSonya : public SozaiBase
{
public:
	SozaiSonya();
	void update() override;
	void draw() const override;
	~SozaiSonya() = default;
	void initSozai() override;
	void trigger(int actionId) override;
private:
	enum launchType {
		NORMAL = 0,
		LONG,
		SILENT
	};

	struct launch {
		int beatNum;
		int launchType;
	};

	void setLayerFront() override;
	void setKey() override;
	void makeSnowBall(int launchType);
	void addSnowLaunch(int, int);
	std::vector<std::unique_ptr<snowBall>> snowBallPtr;
	std::vector<launch> launchList;
	bool avoidFlag = false;
	LONGLONG prevTime;
	LONGLONG prevAvoidTime;					// 連続で回避させない
	sideBlank sideBarL;
	sideBlank sideBarR;
};

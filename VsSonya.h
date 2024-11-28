#pragma once
#include <vector>
#include <memory>
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"
#include "sideBlank.h"
#include "snowBall.h"
#include "BPMManager.h"

class VsSonya : public AbstractScene
{
public:
	VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter);
	~VsSonya() = default;
	void update() override;
	void draw() const override;
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
	int shiwakeMasterHandle;
	int debugSEHandle;
	static const int backgroundNum = 5;
	SozaiManager sozaiManager;
	LONGLONG prevTime;
	BPMManager bpmManager;
	BackGround backGround[backgroundNum];
	sideBlank sideBarL;
	sideBlank sideBarR;
	bool showBar;
	std::vector<std::unique_ptr<snowBall>> snowBallPtr;
	void makeSnowBall(int);
	void addSnowLaunch(int, int);
	int tmp16Beat;						// 1è¨êﬂ16beat
	bool beatChanged;
	std::vector<launch> launchList;
	int score;
	const int MaxScore = 73;
	LONGLONG prevAvoidTime;					// òAë±Ç≈âÒîÇ≥ÇπÇ»Ç¢
	bool avoidFlag;
};


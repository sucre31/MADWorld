#pragma once
#include <Dxlib.h>
#include <vector>
#include <memory>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/BackGround.h"
#include "sideBlank.h"
#include "snowBall.h"
#include "Common/BPMManager.h"

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
	int tmp16Beat;						// 1小節16beat
	bool beatChanged;
	std::vector<launch> launchList;
	int score;
	const int MaxScore = 73;
	LONGLONG prevAvoidTime;					// 連続で回避させない
	bool avoidFlag;
};


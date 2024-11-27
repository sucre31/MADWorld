#pragma once
#include <vector>
#include <memory>
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"
#include "sideBlank.h"
#include "snowBall.h"
class VsSonya : public AbstractScene
{
public:
	VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter);
	~VsSonya() = default;
	void update() override;
	void draw() const override;
private:
	int shiwakeMasterHandle;
	int debugSEHandle;
	static const int backgroundNum = 5;
	SozaiManager sozaiManager;
	LONGLONG prevTime;
	BackGround backGround[backgroundNum];
	sideBlank sideBarL;
	sideBlank sideBarR;
	bool showBar;
	std::vector<std::unique_ptr<snowBall>> snowBallPtr;
	void makeSnowBall();
};


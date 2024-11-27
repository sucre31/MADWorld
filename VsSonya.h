#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"
#include "sideBlank.h"
class VsSonya : public AbstractScene
{
public:
	VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter);
	~VsSonya() = default;
	void update() override;
	void draw() const override;
private:
	int shiwakeMasterHandle;
	static const int backgroundNum = 5;
	SozaiManager sozaiManager;
	LONGLONG prevTime;
	BackGround backGround[backgroundNum];
	sideBlank sideBarL;
	sideBlank sideBarR;
};


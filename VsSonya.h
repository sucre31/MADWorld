#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class VsSonya : public AbstractScene
{
public:
	VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter);
	~VsSonya() = default;
	void update() override;
	void draw() const override;
private:
	int shiwakeMasterHandle;
	SozaiManager sozaiManager;
	LONGLONG prevTime;
};


#pragma once
#include "GameObject.h"
class snowBall : public GameObject
{
public:
	snowBall();
	~snowBall() = default;
	bool update() override;
	void draw() const override;
	void setSEHandle(int handle) { SEHandle = handle; }
	int getState() { return snowState; }
	void setState(int stateNum) { snowState = stateNum; }
private:
	LONGLONG prevTime;
	LONGLONG launchTime;
	LONGLONG hitTime;
	int SEHandle;
	int snowBallGraph;
	int snowBallBreakGraph;
	bool hitChecked;
	int snowState;			// 0:とんでる　1:ヒット　2:破壊アニメ 3:消滅
};


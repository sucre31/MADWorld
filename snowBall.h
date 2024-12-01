#pragma once
#include "GameObject.h"

enum stateSnow {
	FLYING,
	CHECK,
	SONYAHIT,
	AVOID,
	WALLHIT,
	DESTROY,
	KILL
};

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
	int snowState;			// 0:とんでる　1:許容タイミング　2:ソーニャヒット 3:回避成功 4:壁ヒット 5:破壊アニメ 6:消滅
	const int marginTime = 80000;	// 許容時間
};


#pragma once
#include "Common/GameObject/GameObject.h"
#include "System/Define.h"

enum stateSnow {
	FLYING,
	CHECK,
	SONYAHIT,
	AVOID,
	WALLHIT,
	DESTROY,
	KILL
};

enum throwType {
	Normal,
	PARABOLA
};

class snowBall : public GameObject
{
public:
	snowBall(float bpm, float beatNum, throwType type);
	~snowBall() = default;
	bool update() override;
	void draw() const override;
	void setSEHandle(int handle) { SEHandle = handle; }
	int getState() { return snowState; }
	void setState(int stateNum) { snowState = stateNum; }
	void setBpm(float setBpm, float beatNum);
private:
	LONGLONG prevTime;
	LONGLONG launchTime;
	LONGLONG hitTime;
	int SEHandle;
	int snowBallGraph;
	int snowBallBreakGraph;
	int snowState;			// 0:とんでる　1:許容タイミング　2:ソーニャヒット 3:回避成功 4:壁ヒット 5:破壊アニメ 6:消滅
	int marginTime = 80000;	// 許容時間
	float bpm = 160;
	float beatTime;
	float targetTime; //着弾までの時間

	const float startX = 1000;
	const float startY = 450;
	const float targetX = (Define::WIN_W * (1.0 / 4.0) + 70);
	const float targetY = (Define::WIN_H / 2.0) + 160;
	const float arcHeight = 300;
	throwType moveType;
};


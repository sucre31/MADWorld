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
	int snowState;			// 0:�Ƃ�ł�@1:���e�^�C�~���O�@2:�\�[�j���q�b�g 3:��𐬌� 4:�ǃq�b�g 5:�j��A�j�� 6:����
	const int marginTime = 80000;	// ���e����
};


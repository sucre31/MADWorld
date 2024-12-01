#include <Dxlib.h>
#include "snowBall.h"
#include "Image.h"
#include "Sound.h"

snowBall::snowBall() {
	snowBallGraph = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/snowBall.png");
	snowBallBreakGraph = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/snowBallBreak.png");
	posX = 1000;
	posY = 450;
	launchTime = GetNowHiPerformanceCount();
	prevTime = launchTime;
	SEHandle = -1;
	snowState = 0;
	hitTime = stateSnow::FLYING;
}

bool snowBall::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime; // �O�񂩂�̌o�ߎ��Ԃ��v�Z

	if (deltaTime / 16670 >= 1 && snowState != stateSnow::DESTROY) {
		//printfDx("%d\n", deltaTime);
		prevTime = curTime - (deltaTime % 16670);
		posX -= 20.0;
		posY += 2.0;
	}

	if (snowState == stateSnow::FLYING || snowState == stateSnow::CHECK) {
		if (((GetNowHiPerformanceCount() - launchTime) >= 562500 - marginTime) && ((GetNowHiPerformanceCount() - launchTime) <= 562500 + marginTime)) {
			// ���̊ԂɃ{�^�����������Ή�𔻒�
			// ���̒��O�ɉ�����[�V�����������Ă���Ԃ��锻��ɂ���
			//PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK, TRUE);
			snowState = stateSnow::CHECK;
			hitTime = GetNowHiPerformanceCount();
		}
		else if (((GetNowHiPerformanceCount() - launchTime) > 562500 + marginTime)) {
			// ������s
			hitTime = GetNowHiPerformanceCount();
			snowState = stateSnow::SONYAHIT;
		}
	}

	if (posX <= 170 && snowState != stateSnow::DESTROY) {
		snowState = stateSnow::WALLHIT;
		hitTime = GetNowHiPerformanceCount();
	}

	if (snowState == stateSnow::DESTROY && GetNowHiPerformanceCount() - hitTime >= 150000) {
		snowState = stateSnow::KILL;
	}

	return true;
}

void snowBall::draw() const{
	if (snowState == stateSnow::DESTROY) {
		DrawRotaGraph(posX, posY, 0.5, 0.0, snowBallBreakGraph, TRUE, FALSE);
	}
	else {
		DrawRotaGraph(posX, posY, 0.5, 0.0, snowBallGraph, TRUE, FALSE);
	}
}
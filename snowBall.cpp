#include <Dxlib.h>
#include "snowBall.h"
#include "Image.h"
#include "Sound.h"

snowBall::snowBall() {
	snowBallGraph = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/snowBall.png");
	posX = 1080;
	posY = 450;
	launchTime = GetNowHiPerformanceCount();
	prevTime = launchTime;
	hitChecked = false;
	SEHandle = -1;
	snowState = 0;
	hitTime = 0;
}

bool snowBall::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime; // ‘O‰ñ‚©‚ç‚ÌŒo‰ßŽžŠÔ‚ðŒvŽZ

	if (prevTime / 16670 >= 1) {
		prevTime = curTime;
		posX -= 1.0;
		posY += 0.11;
	}
	if (hitChecked == false) {
		if ((GetNowHiPerformanceCount() - launchTime) >= 562500) {
			hitChecked = true;
			//PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK, TRUE);
			snowState = 1;
			hitTime = GetNowHiPerformanceCount();
		}
	}
	else {
		if (GetNowHiPerformanceCount() - hitTime >= 100000) {
			snowState = 3;
		}
	}

	return true;
}

void snowBall::draw() const{
	DrawRotaGraph(posX, posY, 0.5, 0.0, snowBallGraph, TRUE, FALSE);
}
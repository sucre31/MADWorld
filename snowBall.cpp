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
	hitChecked = false;
	SEHandle = -1;
	snowState = 0;
	hitTime = 0;
}

bool snowBall::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime; // ‘O‰ñ‚©‚ç‚ÌŒo‰ßŽžŠÔ‚ðŒvŽZ

	if (deltaTime / 16670 >= 1 && snowState == 0) {
		//printfDx("%d\n", deltaTime);
		prevTime = curTime - (deltaTime % 16670);
		posX -= 20.0;
		posY += 2.0;
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
		if (GetNowHiPerformanceCount() - hitTime >= 150000) {
			snowState = 3;
		}
	}

	return true;
}

void snowBall::draw() const{
	if (snowState == 2) {
		DrawRotaGraph(posX, posY, 0.5, 0.0, snowBallBreakGraph, TRUE, FALSE);
	}
	else {
		DrawRotaGraph(posX, posY, 0.5, 0.0, snowBallGraph, TRUE, FALSE);
	}
}
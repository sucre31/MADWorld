#include <Dxlib.h>
#include "snowBall.h"
#include "Common/Image.h"
#include "Common/Sound.h"

snowBall::snowBall(float bpm, float beatNum, throwType type) {
	snowBallGraph = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/snowBall.png");
	snowBallBreakGraph = Image::getIns()->loadSamples("Assets/Sprites/images/sonya/snowBallBreak.png");
	posX = startX;
	posY = startY;
	launchTime = GetNowHiPerformanceCount();
	prevTime = launchTime;
	SEHandle = -1;
	snowState = 0;
	hitTime = stateSnow::FLYING;
	moveType = type;
	setBpm(bpm, beatNum);
}

/*
@brief 着弾までの時間を測定
@param setBpm 曲のbpm
@param beatNum 何拍待つか
*/
void snowBall::setBpm(float setBpm, float beatNum) {
	bpm = setBpm;
	beatTime = (60.0 / bpm) * 1000000.0;
	targetTime = beatTime * beatNum;
	marginTime = beatTime / 4.0;
}

bool snowBall::update() {
	LONGLONG now = GetNowHiPerformanceCount();
	LONGLONG deltaTime = now - prevTime;
	LONGLONG elapsed = now - launchTime;

	// 進行率
	double t = (double)elapsed / targetTime;

	if (snowState != stateSnow::DESTROY) {

		// 直線補間
		double x = startX + (targetX - startX) * t;
		double y = startY + (targetY - startY) * t;

		// 放物線なら高さを追加
		if (moveType == throwType::PARABOLA) {
			y -= 4.0 * arcHeight * t * (1.0 - t);
		}

		posX = x;
		posY = y;
	}

	// 判定
	if (snowState == stateSnow::FLYING) {
		static LONGLONG prevElapsed = 0;

		// 判定開始
		if (elapsed >= (targetTime - marginTime)) {
			snowState = stateSnow::CHECK;
			hitTime = now;
		}
	}

	if (snowState == stateSnow::CHECK) {
		if (elapsed >= (targetTime + marginTime)) {
			snowState = stateSnow::SONYAHIT;
			hitTime = now;
		}
	}

	// 壁ヒット
	if ((posX <= 170 || posY >= 1000)&& snowState != stateSnow::DESTROY) {
		snowState = stateSnow::WALLHIT;
		hitTime = now;
	}

	// 消滅
	if (snowState == stateSnow::DESTROY && now - hitTime >= 150000) {
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
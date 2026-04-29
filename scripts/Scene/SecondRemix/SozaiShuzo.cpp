#include <Dxlib.h>
#include <nlohmann/json.hpp>
#include "SozaiShuzo.h"
#include "System/FpsControl.h"
using json = nlohmann::json;

SozaiShuzo::SozaiShuzo() {
	sozaiPads[(int)ShuzoSound::Shizukada] = ePad::A;
	initializeFont();
	timer = GetNowCount();


	ws.start();
}

void SozaiShuzo::shoutPlay() {
	sozaiManager->playSozai(sozaiHandles[(int)ShuzoSozai::Shuzo], 1);
	shoutCount++;
}

void SozaiShuzo::update() {
	// webSocket接続ログ
	if (wsConnection) {
		wsConnection = false; // 一回だけ表示
	}

	if (isActive) {
		ws.update();

		heatRatio = ws.getHeatRatio();

		if (ws.consumeBurst()) {
			shoutPlay();
		}

		if (Pad::getIns()->get(sozaiPads[(int)ShuzoSound::Shizukada]) == 1) {
			shoutCount++;
		}

		// 熱量に応じてマスクを動かす
		float triggerRatio = heatRatio / heatThreshold;
		float targetRatio = 1 - (1.0f - triggerRatio) * (1.0f - triggerRatio);
		float speed = 4.0f;
		float dt = FpsControl::getIns()->getDeltaTime();
		visualHeatRatio += (targetRatio - visualHeatRatio) * speed * dt;
		if (visualHeatRatio < 0.001f && targetRatio == 0.0f) {
			visualHeatRatio = 0.0f;
		}

		int heatPosY = heatBasePosY + (heatMaxPosY - heatBasePosY) * visualHeatRatio;
		sozaiManager->setSozaiPos(sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskL], heatLeftPosX, heatPosY);
		sozaiManager->setSozaiPos(sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskR], heatRightPosX, heatPosY);
	}
}

void SozaiShuzo::setLayerFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ShuzoSozai::Shuzo], 1);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ShuzoSozai::ShuzoHeatL], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ShuzoSozai::ShuzoHeatR], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskL], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskR], 3);
}


void SozaiShuzo::draw() const{
	if (isActive) {
		DrawFormatStringToHandle(165, Define::WIN_H - 85, GetColor(255, 255, 255), fontHandle, "残り%d回", shoutMax - shoutCount);
	}
}

void SozaiShuzo::initializeFont() {
	fontHandle = CreateFontToHandle("MS UI Gothic", 75, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 6);
	SetFontSpaceToHandle(-10, fontHandle);
}

void SozaiShuzo::initSozai() {
	sozaiHandles[(int)ShuzoSozai::Shuzo] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/shuzo/shuzoIdle.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)ShuzoSozai::Shuzo], "Assets/Sounds/shuzo/shizukada.wav");
	sozaiManager->addSprite(sozaiHandles[(int)ShuzoSozai::Shuzo], 1, "Assets/Sprites/movie/shuzo/shizukada.mp4");
	sozaiManager->setSozaiEx(sozaiHandles[(int)ShuzoSozai::Shuzo], 2.0);

	sozaiHandles[(int)ShuzoSozai::ShuzoHeatL] = 
		sozaiManager->makeSozai("", "Assets/Sprites/images/shuzo/shuzoHeat.png", heatLeftPosX, (Define::WIN_H / 2.0));
	sozaiHandles[(int)ShuzoSozai::ShuzoHeatR] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/shuzo/shuzoHeat.png", heatRightPosX, (Define::WIN_H / 2.0));
	sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskL] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/shuzo/shuzoHeatMask.png", heatLeftPosX, (Define::WIN_H / 2.0));
	sozaiHandles[(int)ShuzoSozai::ShuzoHeatMaskR] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/shuzo/shuzoHeatMask.png", heatRightPosX, (Define::WIN_H / 2.0));

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
	}
}

void SozaiShuzo::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)ShuzoSozai::Shuzo], sozaiPads[(int)ShuzoSound::Shizukada], 1);
}

void SozaiShuzo::trigger(int actionId) {
	if (actionId == 0) shoutPlay();
}
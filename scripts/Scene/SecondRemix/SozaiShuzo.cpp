#include <Dxlib.h>
#include <nlohmann/json.hpp>
#include "SozaiShuzo.h"
#include "System/FpsControl.h"
using json = nlohmann::json;

SozaiShuzo::SozaiShuzo() {
	sozaiPads[(int)ShuzoSound::Shizukada] = ePad::A;
	initializeFont();
	timer = GetNowCount();


	std::thread([this]() {
		if (ws.connect(L"madheavenwebsocket.onrender.com", L"/")) {
			ws.send(R"({"type": "REGISTER", "role": "game"})"); // サーバー側のロールをgameとして通知
			wsConnection = true;
		}
		else {
			printfDx("Connection Failed.\n");
		}
	}).detach();
}

void SozaiShuzo::shoutPlay() {
	sozaiManager->playSozai(sozaiHandles[(int)ShuzoSozai::Shuzo], 1);
	shoutCount++;
}

void SozaiShuzo::update() {
	// webSocket接続ログ
	if (wsConnection) {
		printfDx("webSocket connected.\n");
		wsConnection = false; // 一回だけ表示
	}

	if (isActive) {
		std::string msg;
		while (ws.pollMessage(msg)) { // pollMessage 内で onMessageChanged が呼ばれる
			try {
				auto data = json::parse(msg);

				if (!data.contains("type")) continue;
				std::string type = data["type"];

				if (type == "CONFIG") {
					this->heatThreshold = data["threshold"];
					printfDx("setThreshold:%f\n", heatThreshold);
					continue;
				}

				// 基本データの取得
				heatRatio = data["heatRatio"];
				float totalHeat = data["totalHeat"];

				// サーバー側でリセットが発生した（BURST）場合
				if (type == "BURST" || heatRatio >= heatThreshold) {
					printfDx("!!! HEAT BURST !!!\n");
					heatRatio = 0;
					shoutPlay();
				}
			}
			catch (const std::exception& e) {
				printfDx("JSON Parse Error: %s\n", e.what());
			}
		}

		if (Pad::getIns()->get(ePad::X) == 1) {
			if (ws.isConnected()) {
				// 現在時刻をミリ秒で取得
				tmpLagTimer = GetNowCount(); // 既存の関数があるならこれを使う
				printfDx("send\n");

				// vote とタイムスタンプを文字列化して送信
				ws.send("1");
			}
		}


		if (Pad::getIns()->get(sozaiPads[(int)ShuzoSound::Shizukada]) == 1) {
			shoutCount++;
		}

		// 熱量に応じてマスクを動かす
		float targetRatio = 1 - (1.0f - heatRatio) * (1.0f - heatRatio);
		float speed = 8.0f;
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
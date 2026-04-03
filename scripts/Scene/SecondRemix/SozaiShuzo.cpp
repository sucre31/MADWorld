#include <Dxlib.h>
#include "SozaiShuzo.h"

SozaiShuzo::SozaiShuzo() {
	sozaiPads[(int)ShuzoSound::Shizukada] = ePad::A;
	initializeFont();
	timer = GetNowCount();

	std::thread([this]() {
		ws.connect(L"madheavenwebsocket.onrender.com", L"/");
		wsConnection = true;
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
			int vote = std::stoi(msg);
			int receiveTime = GetNowCount();
			printfDx("Vote changed! New value: %d\n", vote);
			printfDx("time lag: %dms\n", receiveTime - tmpLagTimer);
			shoutPlay();
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
	}
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

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
		sozaiManager->setSozaiEx(handle, 2.0);
	}
}

void SozaiShuzo::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)ShuzoSozai::Shuzo], sozaiPads[(int)ShuzoSound::Shizukada], 1);
}
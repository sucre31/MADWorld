#include <Dxlib.h>
#include <nlohmann/json.hpp>
#include "SozaiObjection.h"
using json = nlohmann::json;

SozaiObjection::SozaiObjection(){
	sozaiPads[(int)ObjectionSound::NaruhodoIdle] = ePad::L;
	sozaiPads[(int)ObjectionSound::MitsurugiIdle] = ePad::R;
	sozaiPads[(int)ObjectionSound::NaruhodoBass] = ePad::down;
	sozaiPads[(int)ObjectionSound::MitsurugiBass] = ePad::B;
	sozaiPads[(int)ObjectionSound::NaruhodoObjection] = ePad::right;
	sozaiPads[(int)ObjectionSound::MitsurugiObjection] = ePad::A;
	sozaiPads[(int)ObjectionSound::NaruhodoHoldIt] = ePad::left;
	sozaiPads[(int)ObjectionSound::MitsurugiHoldIt] = ePad::Y;
	sozaiPads[(int)ObjectionSound::NaruhodoTakeThat] = ePad::up;
	sozaiPads[(int)ObjectionSound::MitsurugiTakeThat] = ePad::X;

	std::thread([this]() {
		ws.connect(L"madheavenwebsocket.onrender.com", L"/");
		ws.send(R"({"type": "REGISTER", "role": "game"})"); // サーバー側のロールをgameとして通知
		wsConnection = true;
		}).detach();
}

void SozaiObjection::update() {
	if (isActive) {
		std::string msg;
		while (ws.pollMessage(msg)) { // pollMessage 内で onMessageChanged が呼ばれる
			try {
				auto data = json::parse(msg);

				std::string type = data["type"];

				if (type == "CONFIG") {
					this->heatThreshold = data["threshold"];
					continue;
				}

				// 基本データの取得
				float heatRatio = data["heatRatio"];
				float totalHeat = data["totalHeat"];

				// サーバー側でリセットが発生した（BURST）場合
				if (type == "BURST" || heatRatio >= heatThreshold) {
					printfDx("!!! HEAT BURST !!!\n");
					setNaruhodoFront();
					sozaiManager->playSozai(sozaiHandles[(int)ObjectionSozai::Naruhodo], 2);
				}

			}
			catch (const std::exception& e) {
				printfDx("JSON Parse Error: %s\n", e.what());
			}
		}

		for (auto& pair : sozaiPads)
		{
			ObjectionSound sound = (ObjectionSound)pair.first;
			ePad pad = pair.second;

			if (Pad::getIns()->get(pad) == 1)
			{
				switch (sound)
				{
				case ObjectionSound::NaruhodoIdle:
				case ObjectionSound::NaruhodoBass:
				case ObjectionSound::NaruhodoObjection:
				case ObjectionSound::NaruhodoHoldIt:
				case ObjectionSound::NaruhodoTakeThat:
					setNaruhodoFront();
					break;

				case ObjectionSound::MitsurugiIdle:
				case ObjectionSound::MitsurugiBass:
				case ObjectionSound::MitsurugiObjection:
				case ObjectionSound::MitsurugiHoldIt:
				case ObjectionSound::MitsurugiTakeThat:
					setMitsurugiFront();
					break;
				}
			}
		}
	}
}

void SozaiObjection::draw() const {

}

void SozaiObjection::initSozai() {
	float exRate = 3.75;
	// ナルホド
	int naruhodoPosX = (Define::WIN_W / 2.0) + 4;
	int naruhodoPosY = (Define::WIN_H / 2.0) - 65;
	int naruhodoHandle = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/naruhodo/idle/idle0.png", naruhodoPosX, naruhodoPosY);
	sozaiManager->addSound(naruhodoHandle, "Assets/Sounds/phoenixWright/naruhodo/objection.wav");
	for (int i = 0; i < 12; i++) {
		sozaiManager->addSprite(naruhodoHandle, 1, ("Assets/Sprites/images/phoenixWright/naruhodo/objection/objection" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(naruhodoHandle, "Assets/Sounds/phoenixWright/bass.wav");
	for (int i = 0; i < 11; i++) {
		sozaiManager->addSprite(naruhodoHandle, 2, ("Assets/Sprites/images/phoenixWright/naruhodo/bass/bass" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(naruhodoHandle, "Assets/Sounds/phoenixWright/naruhodo/holdIt.wav");
	for (int i = 0; i < 10; i++) {
		sozaiManager->addSprite(naruhodoHandle, 3, ("Assets/Sprites/images/phoenixWright/naruhodo/holdIt/holdIt" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(naruhodoHandle, "Assets/Sounds/phoenixWright/naruhodo/takeThat.wav");
	for (int i = 0; i < 13; i++) {
		sozaiManager->addSprite(naruhodoHandle, 4, ("Assets/Sprites/images/phoenixWright/naruhodo/takeThat/takeThat" + std::to_string(i) + ".png").c_str());
	}

	// ミツルギ
	int mitsurugiPosX = (Define::WIN_W / 2.0) + 2;
	int mitsurugiPosY = (Define::WIN_H / 2.0) + 1;
	int mitsurugiHandle = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/mitsurugi/idle/idle0.png", mitsurugiPosX, mitsurugiPosY);
	for (int i = 0; i < 3; i++) {
		sozaiManager->addSprite(mitsurugiHandle, 0, ("Assets/Sprites/images/phoenixWright/mitsurugi/idle/idle" + std::to_string(i) + ".png").c_str());
	}
	sozaiManager->addSound(mitsurugiHandle, "Assets/Sounds/phoenixWright/mitsurugi/objection.wav");
	for (int i = 0; i < 12; i++) {
		sozaiManager->addSprite(mitsurugiHandle, 1, ("Assets/Sprites/images/phoenixWright/mitsurugi/objection/objection" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(mitsurugiHandle, "Assets/Sounds/phoenixWright/bass.wav");
	for (int i = 0; i < 9; i++) {
		sozaiManager->addSprite(mitsurugiHandle, 2, ("Assets/Sprites/images/phoenixWright/mitsurugi/bass/bass" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(mitsurugiHandle, "Assets/Sounds/phoenixWright/mitsurugi/holdIt.wav");
	for (int i = 0; i < 9; i++) {
		sozaiManager->addSprite(mitsurugiHandle, 3, ("Assets/Sprites/images/phoenixWright/mitsurugi/holdIt/holdIt" + std::to_string(i) + ".png").c_str());
	}

	sozaiManager->addSound(mitsurugiHandle, "Assets/Sounds/phoenixWright/mitsurugi/takeThat.wav");
	for (int i = 0; i < 10; i++) {
		sozaiManager->addSprite(mitsurugiHandle, 4, ("Assets/Sprites/images/phoenixWright/mitsurugi/takeThat/takeThat" + std::to_string(i) + ".png").c_str());
	}

	// テーブル
	int tableOffSet = 64;
	int naruhodoTable = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/table.png", (Define::WIN_W / 2.0), naruhodoPosY + tableOffSet);

	int mitsurugiTable = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/tableFlip.png", (Define::WIN_W / 2.0), naruhodoPosY + tableOffSet);

	// 背景
	int naruhodoBack = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/courtBack1.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	int mitsurugiBack = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/courtBack2.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));

	sozaiHandles[(int)ObjectionSozai::Naruhodo] = naruhodoHandle;
	sozaiHandles[(int)ObjectionSozai::Mitsurugi] = mitsurugiHandle;
	sozaiHandles[(int)ObjectionSozai::NaruhodoTable] = naruhodoTable;
	sozaiHandles[(int)ObjectionSozai::MitsurugiTable] = mitsurugiTable;
	sozaiHandles[(int)ObjectionSozai::NaruhodoBack] = naruhodoBack;
	sozaiHandles[(int)ObjectionSozai::MitsurugiBack] = mitsurugiBack;

	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Naruhodo], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoTable], 4);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Mitsurugi], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiTable], 0);

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiEx(handle, exRate);
		sozaiManager->setReverseFlag(handle, false);
	}

	setActive(false);
}

void SozaiObjection::setLayerFront() {
	if (isNaruhodoTurn) {
		setNaruhodoFront();
	}
	else {
		setMitsurugiFront();
	}
}

void SozaiObjection::setNaruhodoFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Naruhodo], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoTable], 4);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Mitsurugi], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiTable], 0);
}
void SozaiObjection::setMitsurugiFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Naruhodo], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::NaruhodoTable], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::Mitsurugi], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)ObjectionSozai::MitsurugiTable], 4);
}

void SozaiObjection::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Naruhodo], sozaiPads[(int)ObjectionSound::NaruhodoIdle], 0);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Naruhodo], sozaiPads[(int)ObjectionSound::NaruhodoObjection], 1);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Naruhodo], sozaiPads[(int)ObjectionSound::NaruhodoBass], 2);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Naruhodo], sozaiPads[(int)ObjectionSound::NaruhodoHoldIt], 3);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Naruhodo], sozaiPads[(int)ObjectionSound::NaruhodoTakeThat], 4);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Mitsurugi], sozaiPads[(int)ObjectionSound::MitsurugiIdle], 0);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Mitsurugi], sozaiPads[(int)ObjectionSound::MitsurugiObjection], 1);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Mitsurugi], sozaiPads[(int)ObjectionSound::MitsurugiBass], 2);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Mitsurugi], sozaiPads[(int)ObjectionSound::MitsurugiHoldIt], 3);
	sozaiManager->setSozaiKey(sozaiHandles[(int)ObjectionSozai::Mitsurugi], sozaiPads[(int)ObjectionSound::MitsurugiTakeThat], 4);
}


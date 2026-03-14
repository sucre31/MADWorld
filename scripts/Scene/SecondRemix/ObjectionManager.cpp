#include "ObjectionManager.h"

ObjectionManager::ObjectionManager(): sozaiManager(nullptr){
	sozaiPads[ObjectionSound::NaruhodoIdle] = ePad::L;
	sozaiPads[ObjectionSound::MitsurugiIdle] = ePad::R;
	sozaiPads[ObjectionSound::NaruhodoBass] = ePad::down;
	sozaiPads[ObjectionSound::MitsurugiBass] = ePad::B;
	sozaiPads[ObjectionSound::NaruhodoObjection] = ePad::left;
	sozaiPads[ObjectionSound::MitsurugiObjection] = ePad::A;
	sozaiPads[ObjectionSound::NaruhodoHoldIt] = ePad::right;
	sozaiPads[ObjectionSound::MitsurugiHoldIt] = ePad::Y;
	sozaiPads[ObjectionSound::NaruhodoTakeThat] = ePad::up;
	sozaiPads[ObjectionSound::MitsurugiTakeThat] = ePad::X;
}

void ObjectionManager::setSozaiManager(SozaiManager* manager) {
	sozaiManager = manager;
}

void ObjectionManager::update() {
	for (auto& pair : sozaiPads)
	{
		ObjectionSound sound = pair.first;
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

void ObjectionManager::draw() const {

}

void ObjectionManager::initSozai() {
	float exRate = 3.75;
	// ナルホド
	int naruhodoPosY = (Define::WIN_W / 2.0) + 4;
	int naruhodoPosX = (Define::WIN_H / 2.0) - 65;
	int naruhodoHandle = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/naruhodo/idle/idle0.png", naruhodoPosY, naruhodoPosX);
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
	int naruhodoTable = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/table.png", (Define::WIN_W / 2.0), naruhodoPosX + tableOffSet);

	int mitsurugiTable = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/tableFlip.png", (Define::WIN_W / 2.0), naruhodoPosX + tableOffSet);

	// 背景
	int naruhodoBack = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/courtBack1.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	int mitsurugiBack = sozaiManager->makeSozai("", "Assets/Sprites/images/phoenixWright/others/courtBack2.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));

	sozaiHandles[ObjectionSozai::Naruhodo] = naruhodoHandle;
	sozaiHandles[ObjectionSozai::Mitsurugi] = mitsurugiHandle;
	sozaiHandles[ObjectionSozai::NaruhodoTable] = naruhodoTable;
	sozaiHandles[ObjectionSozai::MitsurugiTable] = mitsurugiTable;
	sozaiHandles[ObjectionSozai::NaruhodoBack] = naruhodoBack;
	sozaiHandles[ObjectionSozai::MitsurugiBack] = mitsurugiBack;

	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Naruhodo], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoTable], 4);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Mitsurugi], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiTable], 0);

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiEx(handle, exRate);
		sozaiManager->setReverseFlag(handle, false);
	}

	setKey();
}

void ObjectionManager::setNaruhodoFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Naruhodo], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoTable], 4);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Mitsurugi], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiTable], 0);
}
void ObjectionManager::setMitsurugiFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Naruhodo], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoBack], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::NaruhodoTable], 0);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::Mitsurugi], 3);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiBack], 2);
	sozaiManager->setSozaiLayer(sozaiHandles[ObjectionSozai::MitsurugiTable], 4);
}

void ObjectionManager::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Naruhodo], sozaiPads[ObjectionSound::NaruhodoIdle], 0);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Naruhodo], sozaiPads[ObjectionSound::NaruhodoObjection], 1);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Naruhodo], sozaiPads[ObjectionSound::NaruhodoBass], 2);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Naruhodo], sozaiPads[ObjectionSound::NaruhodoHoldIt], 3);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Naruhodo], sozaiPads[ObjectionSound::NaruhodoTakeThat], 4);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Mitsurugi], sozaiPads[ObjectionSound::MitsurugiIdle], 0);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Mitsurugi], sozaiPads[ObjectionSound::MitsurugiObjection], 1);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Mitsurugi], sozaiPads[ObjectionSound::MitsurugiBass], 2);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Mitsurugi], sozaiPads[ObjectionSound::MitsurugiHoldIt], 3);
	sozaiManager->setSozaiKey(sozaiHandles[ObjectionSozai::Mitsurugi], sozaiPads[ObjectionSound::MitsurugiTakeThat], 4);
}
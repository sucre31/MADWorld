#include "SonyaManager.h"

SonyaManager::SonyaManager() {
	sozaiPads[(int)SonyaSound::Hey] = ePad::A;
	sozaiPads[(int)SonyaSound::Tto] = ePad::B;
	sozaiPads[(int)SonyaSound::Sukiari] = ePad::MAX;
	sozaiPads[(int)SonyaSound::Hit] = ePad::MAX;
}



void SonyaManager::update(){
	if (isActive) {
	}
}

void SonyaManager::draw() const {

}

void SonyaManager::initSozai() {
	std::string basePath = "Assets/Sprites/images/sonya/";

	sozaiHandles[(int)SonyaSozai::Sonya] =
		sozaiManager->makeSozai("", (basePath + "sonya/sonya0.png").c_str(), (Define::WIN_W * (1.0 / 4.0)), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Sonya], "Assets/Sounds/sonya/tto.wav");
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Sonya], "Assets/Sounds/sonya/sonyaHit.wav");

	std::vector<int> nums = { 2, 3, 4, 5, 5, 0 };
	for (int n : nums) {
		std::string path = basePath + "sonya/sonya" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Sonya], 1, path.c_str());
	}

	nums = { 2, 3, 4, 5, 5, 0 };
	for (int n : nums) {
		std::string path = basePath + "sonya/sonya" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Sonya], 2, path.c_str());
	}

	sozaiHandles[(int)SonyaSozai::Yasuna] =
		sozaiManager->makeSozai("", (basePath + "yasuna/yasuna0.png").c_str(), (Define::WIN_W * (3.0 / 4.0)), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Yasuna], "Assets/Sounds/sonya/hey.wav");
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Yasuna], "Assets/Sounds/sonya/sukiari.wav");

	nums = { 1, 2, 3, 4, 1, 0 };
	for (int n : nums) {
		std::string path = basePath + "yasuna/yasuna" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Yasuna], 1, path.c_str());
	}

	nums = { 1, 2, 3, 4, 1, 0 };
	for (int n : nums) {
		std::string path = basePath + "yasuna/yasuna" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Yasuna], 2, path.c_str());
	}

	sozaiManager->setSozaiEx(sozaiHandles[(int)SonyaSozai::Sonya], 2.0);
	sozaiManager->setSozaiEx(sozaiHandles[(int)SonyaSozai::Yasuna], 2.0);

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
	}
	setActive(false);
}

void SonyaManager::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)SonyaSozai::Sonya], sozaiPads[(int)SonyaSound::Tto], 1);
	sozaiManager->setSozaiKey(sozaiHandles[(int)SonyaSozai::Yasuna], sozaiPads[(int)SonyaSound::Hey], 1);
}

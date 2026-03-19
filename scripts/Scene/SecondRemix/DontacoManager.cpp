#include "DontacoManager.h"

DontacoManager::DontacoManager() :sozaiManager(nullptr) {
	sozaiPads[DontacoSound::Don] = ePad::A;
	sozaiPads[DontacoSound::Tacos] = ePad::left;
	sozaiPads[DontacoSound::Tara] = ePad::X;
	sozaiPads[DontacoSound::Don2] = ePad::B;
	sozaiPads[DontacoSound::Tacos2] = ePad::down;
	sozaiPads[DontacoSound::Ta] = ePad::Y;
	sozaiPads[DontacoSound::Do] = ePad::right;
}

void DontacoManager::setSozaiManager(SozaiManager* manager) {
	sozaiManager = manager;
}


void DontacoManager::update() {

}

void DontacoManager::draw() const {

}

void DontacoManager::initSozai() {
	sozaiHandles[DontacoSozai::Dontacos] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/dontaco/dontacos.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/don.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tacos.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tara.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/don2.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tacos2.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/do.wav");
	sozaiManager->addSound(sozaiHandles[DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/ta.wav");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 1, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 2, "Assets/Sprites/movie/Dontaco/tacos.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 3, "Assets/Sprites/movie/Dontaco/ta.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 4, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 5, "Assets/Sprites/movie/Dontaco/tacos.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 6, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[DontacoSozai::Dontacos], 7, "Assets/Sprites/movie/Dontaco/ta.mp4");
	//sozaiHandles[DontacoSozai::Drum] =
	//	sozaiManager->makeSozai("", "Assets/Sprites/movie/kunimeiWakekko/donesia.mp4", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0)));
	sozaiManager->setSozaiEx(sozaiHandles[DontacoSozai::Dontacos], 2.0);
	setActive(false);
}

void DontacoManager::setLayerFront() {
	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiLayer(handle, 1);
		sozaiManager->setReverseFlag(handle, false);
	}
}

void DontacoManager::setLayerBack() {
	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiLayer(handle, -1);
		sozaiManager->setReverseFlag(handle, false);
	}
}

void DontacoManager::setActive(bool flag) {
	if (flag) {
		isActive = true;
		setLayerFront();
		setKey();
	}
	else {
		isActive = false;
		setLayerBack();
		resetKey();
	}
}

void DontacoManager::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Don], 1);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Tacos], 2);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Tara], 3);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Don2], 4);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Tacos2], 5);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Do], 6);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], sozaiPads[DontacoSound::Ta], 7);
	sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Dontacos], ePad::up, 7);
	//sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Drum], sozaiPads[DontacoSound::Drum1], 0);
}

void DontacoManager::resetKey() {
	sozaiManager->resetSozaiKey(sozaiHandles[DontacoSozai::Dontacos]);
	//sozaiManager->resetSozaiKey(sozaiHandles[DontacoSozai::Drum]);
}
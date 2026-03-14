#include "DonesiaManager.h"

DonesiaManager::DonesiaManager():sozaiManager(nullptr) {
	sozaiPads[DonesiaSound::In] = ePad::A;
	sozaiPads[DonesiaSound::Donesia] = ePad::B;
}

void DonesiaManager::setSozaiManager(SozaiManager* manager) {
	sozaiManager = manager;
}


void DonesiaManager::update() {

}

void DonesiaManager::draw() const {

}

void DonesiaManager::initSozai() {
	sozaiHandles[DonesiaSozai::Kawahara] =
		sozaiManager->makeSozai("Assets/Sounds/kunimeiWakekko/in.wav", "Assets/Sprites/movie/kunimeiWakekko/in.mp4", 660 + 306, (Define::WIN_H / 2.0));
	sozaiHandles[DonesiaSozai::Goto] =
		sozaiManager->makeSozai("Assets/Sounds/kunimeiWakekko/donesia.wav", "Assets/Sprites/movie/kunimeiWakekko/donesia.mp4", 330, (Define::WIN_H / 2.0));
	setActive(false);
}

void DonesiaManager::setLayerFront() {
	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiLayer(handle, 1);
		sozaiManager->setReverseFlag(handle, false);
	}
}

void DonesiaManager::setLayerBack() {
	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;

		sozaiManager->setSozaiLayer(handle, -1);
		sozaiManager->setReverseFlag(handle, false);
	}
}

void DonesiaManager::setActive(bool flag) {
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

void DonesiaManager::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[DonesiaSozai::Kawahara], sozaiPads[DonesiaSound::In], 0);
	sozaiManager->setSozaiKey(sozaiHandles[DonesiaSozai::Goto], sozaiPads[DonesiaSound::Donesia], 0);
}

void DonesiaManager::resetKey() {
	sozaiManager->resetSozaiKey(sozaiHandles[DonesiaSozai::Kawahara]);
	sozaiManager->resetSozaiKey(sozaiHandles[DonesiaSozai::Goto]);
}
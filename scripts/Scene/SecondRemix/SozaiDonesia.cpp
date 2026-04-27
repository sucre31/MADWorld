#include "SozaiDonesia.h"

SozaiDonesia::SozaiDonesia() {
	sozaiPads[(int)DonesiaSound::In] = ePad::MAX;
	sozaiPads[(int)DonesiaSound::Donesia] = ePad::A;
}

void SozaiDonesia::update() {

}

void SozaiDonesia::draw() const {

}

void SozaiDonesia::initSozai() {
	sozaiHandles[(int)DonesiaSozai::Kawahara] =
		sozaiManager->makeSozai("Assets/Sounds/kunimeiWakekko/in.wav", "Assets/Sprites/movie/kunimeiWakekko/in.mp4", 660 + 306, (Define::WIN_H / 2.0));
	sozaiHandles[(int)DonesiaSozai::Goto] =
		sozaiManager->makeSozai("Assets/Sounds/kunimeiWakekko/donesia.wav", "Assets/Sprites/movie/kunimeiWakekko/donesia.mp4", 330, (Define::WIN_H / 2.0));

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
	}

	setActive(false);
}

void SozaiDonesia::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)DonesiaSozai::Kawahara], sozaiPads[(int)DonesiaSound::In], 0);
	sozaiManager->setSozaiKey(sozaiHandles[(int)DonesiaSozai::Goto], sozaiPads[(int)DonesiaSound::Donesia], 0);
}

void SozaiDonesia::trigger(int actionId) {
	if (actionId == 0) {
		sozaiManager->playSozai(
			sozaiHandles[(int)DonesiaSozai::Kawahara],
			0
		);
	}
	else {
		sozaiManager->playSozai(
			sozaiHandles[(int)DonesiaSozai::Goto],
			0
		);
	}
}
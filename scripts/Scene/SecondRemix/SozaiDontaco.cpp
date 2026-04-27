#include "SozaiDontaco.h"

SozaiDontaco::SozaiDontaco(){
	sozaiPads[(int)DontacoSound::Don] = ePad::A;
	sozaiPads[(int)DontacoSound::Tacos] = ePad::left;
	sozaiPads[(int)DontacoSound::Tara] = ePad::X;
	sozaiPads[(int)DontacoSound::Don2] = ePad::B;
	sozaiPads[(int)DontacoSound::Tacos2] = ePad::down;
	sozaiPads[(int)DontacoSound::Ta] = ePad::Y;
	sozaiPads[(int)DontacoSound::Do] = ePad::right;
	sozaiPads[(int)DontacoSound::DrumDon] = ePad::A;
	sozaiPads[(int)DontacoSound::DrumTacos] = ePad::left;
	sozaiPads[(int)DontacoSound::DrumTara] = ePad::X;
	sozaiPads[(int)DontacoSound::DrumDon2] = ePad::B;
	sozaiPads[(int)DontacoSound::DrumTacos2] = ePad::down;
	sozaiPads[(int)DontacoSound::DrumTa] = ePad::Y;
	sozaiPads[(int)DontacoSound::DrumDo] = ePad::right;
}

void SozaiDontaco::update() {
	if (isActive) {
		if (Pad::getIns()->get(ePad::L) >= 1) {
			if (useDrum != false) {
				useDrum = false;
				resetKey();
				setKey();
			}
		}
		else {
			if (useDrum != true) {
				useDrum = true;
				resetKey();
				setKey();
			}
		}
	}
}

void SozaiDontaco::draw() const {

}

void SozaiDontaco::initSozai() {
	sozaiHandles[(int)DontacoSozai::Dontacos] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/dontaco/dontacos.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/don.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tacos.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tara.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/don2.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/tacos2.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/do.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Dontacos], "Assets/Sounds/dontaco/Remix2/ta.wav");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 1, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 2, "Assets/Sprites/movie/Dontaco/tacos.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 3, "Assets/Sprites/movie/Dontaco/ta.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 4, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 5, "Assets/Sprites/movie/Dontaco/tacos.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 6, "Assets/Sprites/movie/Dontaco/don.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Dontacos], 7, "Assets/Sprites/movie/Dontaco/ta.mp4");

	sozaiHandles[(int)DontacoSozai::Drum] =
		sozaiManager->makeSozai("", "Assets/Sprites/images/dontaco/dontacos.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumDon.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumTacos.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumTara.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumDon2.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumTacos2.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumDo.wav");
	sozaiManager->addSound(sozaiHandles[(int)DontacoSozai::Drum], "Assets/Sounds/dontaco/Remix2/drumTa.wav");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 1, "Assets/Sprites/movie/Dontaco/drumDon.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 2, "Assets/Sprites/movie/Dontaco/drumTacos.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 3, "Assets/Sprites/movie/Dontaco/drumTa.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 4, "Assets/Sprites/movie/Dontaco/drumDon2.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 5, "Assets/Sprites/movie/Dontaco/drumTacos2.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 6, "Assets/Sprites/movie/Dontaco/drumDon.mp4");
	sozaiManager->addSprite(sozaiHandles[(int)DontacoSozai::Drum], 7, "Assets/Sprites/movie/Dontaco/drumTa.mp4");
	sozaiManager->setSozaiEx(sozaiHandles[(int)DontacoSozai::Dontacos], 2.0);
	sozaiManager->setSozaiEx(sozaiHandles[(int)DontacoSozai::Drum], 2.0);

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
	}
	setActive(false);
}

void SozaiDontaco::setKey() {
	if (!useDrum) {
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Don], 1);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Tacos], 2);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Tara], 3);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Don2], 4);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Tacos2], 5);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Do], 6);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], sozaiPads[(int)DontacoSound::Ta], 7);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Dontacos], ePad::up, 7);
	}
	else {
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumDon], 1);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumTacos], 2);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumTara], 3);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumDon2], 4);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumTacos2], 5);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumDo], 6);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], sozaiPads[(int)DontacoSound::DrumTa], 7);
		sozaiManager->setSozaiKey(sozaiHandles[(int)DontacoSozai::Drum], ePad::up, 7);
	}
	//sozaiManager->setSozaiKey(sozaiHandles[DontacoSozai::Drum], sozaiPads[DontacoSound::Drum1], 0);
}

void SozaiDontaco::trigger(int actionId) {
	sozaiManager->playSozai(
		useDrum ? sozaiHandles[(int)DontacoSozai::Drum]
		: sozaiHandles[(int)DontacoSozai::Dontacos],
		actionId
	);
}
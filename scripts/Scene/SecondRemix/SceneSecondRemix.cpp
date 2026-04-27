#include <algorithm>
#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	int back = sozaiManager.makeSozai("", "Assets/Sprites/images/secondRemix/back.png", (int)(Define::WIN_W / 2.0), (int)(Define::WIN_H / 2.0));
	sozaiManager.setSozaiLayer(back, 0);

	sozaies = {
		&objection,
		&donesia,
		&dontaco,
		&sonya,
		&shuzo
	};

	for (auto* sozai: sozaies) {
		sozai->setSozaiManager(&sozaiManager);
		sozai->initSozai();
		sozai->setActive(false);
	}

	musicManager.LoadMusic("tutorial", "Assets/Sounds/dontaco/BGM/tutorialBeat.wav");
	musicManager.LoadMusic("backBeat", "Assets/Sounds/dontaco/BGM/backBeat.wav");
	musicManager.LoadMusic("remix2", "Assets/Sounds/Remix2/remix2.wav");

	bgmName = "remix2";
	musicManager.Play(bgmName, true);
	sonya.startMusic();

	noteManager.loadFromFile("");

	prevMangerIndex = -1;
	activeManagerIndex = 0;
}

void SceneSecondRemix::update() {

	if (Pad::getIns()->get(ePad::ZL) == 1) {
		activeManagerIndex--;
		activeManagerIndex = std::clamp(activeManagerIndex, 0, (int)sozaies.size() - 1);
	}

	if (Pad::getIns()->get(ePad::change) >= 1 && Pad::getIns()->get(ePad::ZL) == 1) {
		if (musicManager.IsPlaying()) {
			musicManager.Stop();
		}
		else {
			musicManager.Play(bgmName, true);
		}
	}

	if (Pad::getIns()->get(ePad::ZR) == 1) {
		activeManagerIndex++;
		activeManagerIndex = std::clamp(activeManagerIndex, 0, (int)sozaies.size() - 1);
	}

	if (Pad::getIns()->get(ePad::start) >= 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
		return;
	}


	if (prevMangerIndex != activeManagerIndex) {
		if (prevMangerIndex != -1) {
			sozaies[prevMangerIndex]->setActive(false);
		}
		sozaies[activeManagerIndex]->setActive(true);

		prevMangerIndex = activeManagerIndex;
	}

	for (SozaiBase* sozai : sozaies) {
		sozai->update();
	}

	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
	for (SozaiBase* sozai : sozaies) {
		sozai->draw();
	}
}
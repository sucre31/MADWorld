#include <algorithm>
#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	int back = sozaiManager.makeSozai("", "Assets/Sprites/images/secondRemix/back.png", (int)(Define::WIN_W / 2.0), (int)(Define::WIN_H / 2.0));
	sozaiManager.setSozaiLayer(back, 0);

	bpmManager = std::make_shared<BPMManager>();

	sozaies = {
		&objection,
		&donesia,
		&dontaco,
		&sonya,
		&shuzo
	};

	for (auto* sozai: sozaies) {
		sozai->setSozaiManager(&sozaiManager);
		sozai->setBPMManager(bpmManager);
		sozai->initSozai();
		sozai->setActive(false);
	}

	musicManager.LoadMusic("tutorial", "Assets/Sounds/dontaco/BGM/tutorialBeat.wav");
	musicManager.LoadMusic("backBeat", "Assets/Sounds/dontaco/BGM/backBeat.wav");
	musicManager.LoadMusic("remix2", "Assets/Sounds/Remix2/remix2.wav");

	bgmName = "remix2";
	musicManager.Play(bgmName, false);
	bpmManager->setBPM(132);
	bpmManager->startMusic();

	noteManager.loadFromFile("");

	prevMangerIndex = -1;
	activeManagerIndex = 0;


	// とりあえずハードコードで素材管理
	events = {
		{16, ActionType::AutoPlay, 3, false},
		{24, ActionType::AutoPlay, 2, false},
		{32, ActionType::AutoPlay, 3, false},
		{40, ActionType::AutoPlay, 2, false},
		{48, ActionType::AutoPlay, 3, false},
		{56, ActionType::AutoPlay, 2, false},
		{64, ActionType::AutoPlay, 3, false},
		{72, ActionType::AutoPlay, 2, false},
		{80, ActionType::AutoPlay, 4, false},
		{112, ActionType::AutoPlay, 2, false},
		{136, ActionType::AutoPlay, 1, false},
		{144, ActionType::AutoPlay, 2, false},
		{168, ActionType::AutoPlay, 1, false},
		{176, ActionType::AutoPlay, 0, false},
		{240, ActionType::AutoPlay, 3, false},
		{248, ActionType::AutoPlay, 1, false},
		{256, ActionType::AutoPlay, 4, false},
		{264, ActionType::AutoPlay, 0, false},
	};
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

	// 素材管理
	currentBeat = bpmManager->getCurrentBeatNum();
	for (auto& e : events) {
		if (!e.triggered && currentBeat >= e.beat - 0.5) {	// 少し早く切り替え
			e.triggered = true;

			if (e.actionType == ActionType::SozaiChange) {
				switch (e.param) {
				case 0:
					activeManagerIndex = 0;
					break;
				case 1:
					activeManagerIndex = 1;
					break;
				case 2:
					activeManagerIndex = 2;
					break;
				case 3:
					activeManagerIndex = 3;
					break;
				case 4:
					activeManagerIndex = 4;
					break;
				}
			}
			else if (e.actionType == ActionType::AutoPlay) {

			}
		}
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
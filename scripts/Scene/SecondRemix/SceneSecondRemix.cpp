#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include "SceneSecondRemix.h"

using json = nlohmann::json;

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
	activeManagerIndex = 3;


	// オートプレイ読み込み
	std::ifstream ifs("Assets/Score/remix2.json");
	json j;
	ifs >> j;

	for (auto& e : j) {
		SozaiEvent ev;

		// bar + beat → 通しbeatに変換
		int bar = e["bar"];
		double beatInBar = e["beat"];
		int beatsPerBar = 4; // ← 拍子（あとでBPMManagerから取ってもいい）

		ev.beat = (bar - 1) * beatsPerBar + (beatInBar - 1);

		// type
		std::string type = e["type"];
		if (type == "SozaiChange") ev.actionType = ActionType::SozaiChange;
		else if (type == "AutoPlay") ev.actionType = ActionType::AutoPlay;

		// target
		std::string target = e["target"];
		if (target == "Sonya") ev.targetSozai = SozaiType::Sonya;
		else if (target == "Dontaco") ev.targetSozai = SozaiType::Dontaco;
		else if (target == "Shuzo") ev.targetSozai = SozaiType::Shuzo;
		else if (target == "Donesia") ev.targetSozai = SozaiType::Donesia;
		else if (target == "Objection") ev.targetSozai = SozaiType::Objection;

		// actionId
		ev.actionId = e.value("actionId", 0);

		ev.triggered = false;

		events.push_back(ev);
	}

	//events = {
	//	{16, SozaiChange, Sonya},
	//	{24, SozaiChange, Dontaco},
	//	{32, SozaiChange, Sonya},
	//	{40, SozaiChange, Dontaco},
	//	{48, SozaiChange, Dontaco},
	//	{64, SozaiChange, Sonya},
	//	{72, SozaiChange, Dontaco},
	//	{80, SozaiChange, Shuzo},
	//	{112, SozaiChange, Dontaco},
	//	{136, SozaiChange, Donesia},
	//	{144, SozaiChange, Dontaco},
	//	{168, SozaiChange, Donesia},
	//	{176, SozaiChange, Objection},
	//	{240, SozaiChange, Sonya},
	//	{248, SozaiChange, Donesia},
	//	{256, SozaiChange, Shuzo},
	//	{264, SozaiChange, Objection},
	//	{16, AutoPlay, Sonya, 0},
	//};
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
	prevBeat = currentBeat;
	currentBeat = bpmManager->getCurrentBeatNum();
	for (auto& e : events) {
		if (!e.triggered && prevBeat < e.beat && currentBeat >= e.beat) {
			e.triggered = true;

			if (e.actionType == ActionType::SozaiChange) {
				switch (e.targetSozai) {
				case Objection:
					activeManagerIndex = 0;
					break;
				case Donesia:
					activeManagerIndex = 1;
					break;
				case Dontaco:
					activeManagerIndex = 2;
					break;
				case Sonya:
					activeManagerIndex = 3;
					break;
				case Shuzo:
					activeManagerIndex = 4;
					break;
				}
			}
			else if (e.actionType == ActionType::AutoPlay) {
				sozaies[e.targetSozai]->trigger(e.actionId);
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
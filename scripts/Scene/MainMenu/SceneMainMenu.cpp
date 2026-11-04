#include <DxLib.h>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "SceneMainMenu.h"
#include "Common/Sound.h"
#include "Common/Image.h"
#include "Common/Time.h"
#include "System/Pad.h"
#include "System/FpsControl.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

SceneMainMenu::SceneMainMenu(IOnSceneChangedListener* impl, const Parameter& parameter) : validIconNum(0) , selectIconNo(-1), AbstractScene(impl, parameter)
{
	cursorIns.loadCursorImage("Assets/Sprites/images/MainMenu/cursor.png");
	backGround.loadBackImage("Assets/Sprites/images/MainMenu/UISample.png");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	musicHandle = Sound::getIns()->loadSamples("Assets/Sounds/Menu/Menu2.wav");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, TRUE);

	icon[0].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail1.png");
	icon[1].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail2.png");
	icon[2].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail3.png");
	icon[3].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail4.png");
	icon[4].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail5.png");
	icon[5].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail6.png");
	icon[6].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail7.png");
	icon[7].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail7.png");
	icon[8].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail8.png");
	icon[9].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail9.png");
	icon[10].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail10.png");
	for (int i = 0; i < iconNum; i++) {
		icon[i].setPos(130 + 240 * (i / 4), 160 + (i % 4) * 133);
		icon[i].enableIconFunc(true);
		validIconNum++;
	}
	LoadDynamicStages();

	SetMouseDispFlag(FALSE);	// カーソル非表示
}

void SceneMainMenu::update()
{
	int cursorX, cursorY;
	double deltaTime = Time::getIns()->getDeltaTime();
	cursorX = cursorIns.getCursorPosX();
	cursorY = cursorIns.getCursorPosY();
	double speedRate = 300.0;
	selectIconNo = -1;
	bool isHit;

	if (Pad::getIns()->get(ePad::R) == 1) {
		if (currentState == MenuState::MainMenu) {
			currentState = MenuState::ExtraMenu;
		}
		else {
			currentState = MenuState::MainMenu;
		}
	}

	if (currentState == MenuState::MainMenu) {
		for (int i = 0; i < dynamicStageCount; i++) {
			if (dynamicIcons[i]->checkCursorHit(cursorX, cursorY)) {
				selectIconNo = i;
			}
		}
	}
	else {
		for (int i = 0; i < validIconNum; i++) {
			if (icon[i].checkCursorHit(cursorX, cursorY)) {
				selectIconNo = i;
			}
		}
	}


	if (Pad::getIns()->get(ePad::Y) >= 1) {
		speedRate = 500.0;
	}
	if (Pad::getIns()->get(ePad::A) >= 1 && selectIconNo != -1) {
		// アイコンあればシーンチェンジ
		Parameter parameter;
		StopSoundMem(musicHandle);
		const bool stackClear = true;
		if (currentState == MenuState::MainMenu) {
			parameter.SetString("jsonFilePath", jsonPaths[selectIconNo]);
			_implSceneChanged->onSceneChanged(eScene::JudgeGame, parameter, stackClear);
		}
		else {
			int sceneNum = getIconScene(selectIconNo);
			if (sceneNum != -1) {
				_implSceneChanged->onSceneChanged(eScene(sceneNum), parameter, stackClear);
			}
		}
	}

	if (Pad::getIns()->get(ePad::B) == 1) {
		StopSoundMem(musicHandle);
		//SetMouseDispFlag(TRUE);
		Parameter parameter;
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
	if (Pad::getIns()->get(ePad::up) >= 1) {
		cursorIns.plusPos(0, -1 * speedRate * deltaTime);
	}
	if (Pad::getIns()->get(ePad::down) >= 1) {
		cursorIns.plusPos(0, 1 * speedRate * deltaTime);
	}
	if (Pad::getIns()->get(ePad::right) >= 1) {
		cursorIns.plusPos(1 * speedRate * deltaTime, 0);
	}
	if (Pad::getIns()->get(ePad::left) >= 1) {
		cursorIns.plusPos(-1 * speedRate * deltaTime, 0);
	}
}

void SceneMainMenu::draw() const
{
	backGround.draw();

	if (currentState == MenuState::MainMenu) {
		for (int i = 0; i < dynamicStageCount; i++) {
			dynamicIcons[i]->draw();
		}
	}
	else {
		for (int i = 0; i < validIconNum; i++) {
			icon[i].draw();
		}
		DrawString(10, 10, "EXTRA STAGES", GetColor(255, 255, 255));
	}
	cursorIns.draw();
}

void SceneMainMenu::LoadDynamicStages() {
	// JSONファイルのパスを取得する処理を実装する
	std::string targetDir = "Assets/Stages/";

	if (!fs::exists(targetDir)) return;

	for (const auto& entry : fs::directory_iterator(targetDir)) {
		if (entry.path().extension() == ".json") {
			std::string jsonPath = entry.path().string();
			jsonPaths.push_back(jsonPath);

			std::ifstream file(jsonPath);
			if (file.is_open()) {
				try {
					json j;
					file >> j;

					std::string thumbPath = j["meta"].value("thumbnail", "Assets/Sprites/images/default_thumb.png");

					auto newIcon = std::make_unique<gameIcon>();
					newIcon->loadThumbnail(thumbPath.c_str());
					newIcon->setPos(130 + 240 * (dynamicStageCount / 4), 160 + (dynamicStageCount % 4) * 133);
					newIcon->enableIconFunc(true);

					dynamicIcons.push_back(std::move(newIcon));
					dynamicStageCount++;
				}
				catch (const std::exception& e) {
					// JSONのパースエラーが発生した場合の処理
					printfDx("JSON Parse Error: %s\n", jsonPath.c_str());
				}
			}
		}
	}
}

/*
@brief アイコン番号とシーン番号を対応させる
*/
int SceneMainMenu::getIconScene(int iconNum) {
	switch (iconNum) {
	case 0:
		return eScene::Sonya;
	case 1:
		return eScene::LoveSong;
	case 2:
		return eScene::LightPlane;
	case 3:
		return eScene::Alice;
	case 4:
		return eScene::Starguitar;
	case 5:
		return eScene::Seikan;
	case 6:
		return eScene::Snippet;
	case 7:
		return eScene::RealEdit;
	case 8:
		return eScene::Pizza;
	case 9:
		return eScene::SecondRemix;
	case 10:
		return eScene::RobotSampler;
	default:
		return -1;
	}
}
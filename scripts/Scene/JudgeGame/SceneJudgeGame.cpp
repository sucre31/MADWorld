#include "SceneJudgeGame.h"
#include "Common/Event/EventLoader.h"
#include "Common/Sound.h"
#include "Common/Image.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ePad stringToPad(const std::string& keyStr) {
	if (keyStr == "up") return ePad::up;
	if (keyStr == "down") return ePad::down;
	if (keyStr == "left") return ePad::left;
	if (keyStr == "right") return ePad::right;
	if (keyStr == "A") return ePad::A;
	if (keyStr == "B") return ePad::B;
	if (keyStr == "X") return ePad::X;
	if (keyStr == "Y") return ePad::Y;
	if (keyStr == "L") return ePad::L;
	if (keyStr == "R") return ePad::R;
	return ePad::MAX;
}

SceneJudgeGame::SceneJudgeGame(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter)
{
	std::string jsonFilePath = parameter.GetString("jsonFilePath");


	// 譜面情報の読み込み
	std::ifstream file(jsonFilePath);
	int bpm = 140; // デフォルト
	int beatsPerBar = 4;
	if (file.is_open()) {
		json j;
		file >> j;
		if (j.contains("meta")) {
			bpm = j["meta"].value("bpm", 140);
			beatsPerBar = j["meta"].value("beatsPerBar", 4);
		}
	}
	noteManager = std::make_unique<NoteManager>(bpm, beatsPerBar, &sozaiManager);

	// アセットの読み込み処理
	loadFromJson(jsonFilePath);

	noteManager->loadFromFile(jsonFilePath);



	registerActions();
	events = EventLoader::loadFromFile(jsonFilePath, actionRegistry);

	// BGMを再生し、BPMManagerに時間を監視させる
	if (bgmHandle != -1) {
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, TRUE);
		bpmManager.startMusic(bgmHandle);
	}
}

void SceneJudgeGame::loadFromJson(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) return;

	try {
		json j;
		file >> j;

		// BGMの読み込み
		if (j.contains("meta")) {
			double bpm = j["meta"].value("bpm", 120.0);
			bpmManager.setBPM(bpm);

			std::string bgmPath = j["meta"].value("bgm", "");
			if (!bgmPath.empty()) {
				bgmHandle = Sound::getIns()->loadSamples(bgmPath.c_str());
			}
		}

		// 各種アセットの読み込み
		if (j.contains("assets") && j["assets"].is_array()) {
			for (const auto& asset : j["assets"]) {
				// typeが設定されていない場合は "single" として扱う
				std::string type = asset.value("type", "single");
				float x = asset.value("x", 640.0f);
				float y = asset.value("y", 360.0f);
				float scale = asset.value("scale", 1.0f);
				bool isReverse = asset.value("isReverse", false);
				bool isDrum = asset.value("isDrum", false);

				if (type == "single") {
					std::string soundPath = asset.value("sound", "");
					std::string moviePath = asset.value("movie", "");
					int id = sozaiManager.makeSozai(soundPath.c_str(), moviePath.c_str(), x, y);

					// 拡縮やフラグの設定
					sozaiManager.setSozaiEx(id, scale);
					sozaiManager.setReverseFlag(id, isReverse);
					sozaiManager.setDrumFlag(id, isDrum);

					// コントローラーのボタン割り当て（JSONに "padKeys" 配列がある場合のみ）
					if (asset.contains("padKeys") && asset["padKeys"].is_array()) {
						for (const auto& keyStr : asset["padKeys"]) {
							ePad padEnum = stringToPad(keyStr.get<std::string>());
							if (padEnum != ePad::MAX) {
								// SozaiManagerにキーを設定
								sozaiManager.setSozaiKey(id, padEnum, 0);
							}
						}
					}
				}
				else if (type == "multi") {
					if (asset.contains("items") && asset["items"].is_array()) {
						int id = -1;
						int soundIndex = 0;

						for (const auto& item : asset["items"]) {
							std::string soundPath = item.value("sound", "");
							std::string moviePath = item.value("movie", "");

							// ベースのSozaiを作成
							if (id == -1) {
								id = sozaiManager.makeSozai(soundPath.c_str(), moviePath.c_str(), x, y);
								sozaiManager.setSozaiEx(id, scale);
								sozaiManager.setReverseFlag(id, isReverse);
								sozaiManager.setDrumFlag(id, isDrum);
								sozaiManager.setMultiSound(id, true);
							}
							// 作成したSozaiに追加
							else {
								sozaiManager.addSound(id, soundPath.c_str());
								sozaiManager.addSprite(id, soundIndex, moviePath.c_str());
							}

							if (item.contains("padKeys") && item["padKeys"].is_array()) {
								for (const auto& keyStr : item["padKeys"]) {
									ePad padEnum = stringToPad(keyStr.get<std::string>());
									if (padEnum != ePad::MAX) {
										sozaiManager.setSozaiKey(id, padEnum, soundIndex);
									}
								}
							}
							// 単体指定された場合にも対応
							else if (item.contains("padKey") && item["padKey"].is_string()) {
								ePad padEnum = stringToPad(item["padKey"].get<std::string>());
								if (padEnum != ePad::MAX) {
									sozaiManager.setSozaiKey(id, padEnum, soundIndex);
								}
							}
							soundIndex++;
						}
					}
				}
			}
		}
	}
	catch (const std::exception& e) {
		// JSONのパースエラーやファイル読み込みエラーを処理
		printfDx("JSON Parse Error: %s\n", e.what());
	}
}
void SceneJudgeGame::update() {
	double currentBeat = bpmManager.getCurrentBeatNum();

	sozaiManager.update();

	if (Pad::getIns()->get(ePad::start) == 1) {
		StopSoundMem(bgmHandle);
		Parameter parameter;
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, true);
	}
}

void SceneJudgeGame::draw() const {
	DrawBox(0, 0, 1280, 720, GetColor(255, 0, 0), TRUE);
	sozaiManager.draw();
}

void SceneJudgeGame::registerActions() {
	// ここで譜面のアクションを登録する
	// 例: actionRegistry.registerAction("playSound", [](const TimedEvent& event) { ... });
}
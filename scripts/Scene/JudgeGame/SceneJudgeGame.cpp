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
	AppLogAdd("SceneJudgeGame::Constructor: Start\n");
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
	noteUIManager = std::make_unique<NoteUIManager>(*noteManager, sozaiManager);

	// アセットの読み込み処理
	AppLogAdd("SceneJudgeGame::Constructor: loadFromJson start\n");
	loadFromJson(jsonFilePath);
	AppLogAdd("SceneJudgeGame::Constructor: loadFromJson end\n");

	noteManager->loadFromFile(jsonFilePath);

	noteManager->eventCallback = [this](const Note& note) {
		sozaiManager.playSozai(note.inputId, note.soundIndex);
	};

	noteManager->setUseAutoPlay(false);

	registerActions();
	events = EventLoader::loadFromFile(jsonFilePath, actionRegistry);

	beatDurationMs = 60000.0 / bpm;
	countdownDurationMs = static_cast<int>(beatDurationMs * 4.0); // 4拍分待機する

	currentState = eGameState::Ready;
	stateStartTime = GetNowCount();
	AppLogAdd("SceneJudgeGame::Constructor: End\n");
}

void SceneJudgeGame::loadFromJson(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		AppLogAdd("loadFromJson: Failed to open file\n");
		return;
	}

	try {
		json j;
		file >> j;

		// BGMの読み込み
		AppLogAdd("loadFromJson: Loading BGM\n");
		if (j.contains("meta")) {
			double bpm = j["meta"].value("bpm", 120.0);
			bpmManager.setBPM(bpm);

			std::string bgmPath = j["meta"].value("bgm", "");
			if (!bgmPath.empty()) {
				bgmHandle = Sound::getIns()->loadSamples(bgmPath.c_str());
			}
			noteManager->setBGMHandle(bgmHandle);
		}

		// 各種アセットの読み込み
		AppLogAdd("loadFromJson: Loading Assets\n");
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
		AppLogAdd("loadFromJson: Exception caught: %s\n", e.what());
		printfDx("JSON Parse Error: %s\n", e.what());
	}
}
void SceneJudgeGame::update() {
	int now = GetNowCount();

	if (currentState == eGameState::Ready) {
		int elapsed = now - stateStartTime;
		int remainMs = countdownDurationMs - elapsed;

		// マイナスの時間を手動でNoteManagerに教える
		noteManager->setCurrentTimeMs(-remainMs);

		sozaiManager.update();
		noteManager->update();

		if (remainMs <= 0) {
			currentState = eGameState::Playing;
			if (bgmHandle != -1) {
				PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, TRUE);
				noteManager->startPlay();
				bpmManager.startMusic(bgmHandle);
			}
		}
	}
	else if (currentState == eGameState::Playing) {
		double currentBeat = bpmManager.getCurrentBeatNum();

		sozaiManager.update();
		noteManager->update();

		for (int p = 0; p < (int)ePad::MAX; p++) {
			if (Pad::getIns()->get(static_cast<ePad>(p)) == 1) {
				noteManager->judgeInput(static_cast<ePad>(p));
			}
		}

		// 途中退出 (STARTボタン)
		if (Pad::getIns()->get(ePad::start) == 1) {
			StopSoundMem(bgmHandle);
			sozaiManager.clearAll();
			Parameter parameter;
			_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, true);
			return;
		}

		// BGMの再生が終了したかチェックし、リザルトへ移行
		if (bgmHandle != -1 && CheckSoundMem(bgmHandle) == 0) {
			resultTimeCounter = now;
			currentState = eGameState::Result;
		}
	}
	else if (currentState == eGameState::Result) {
		if (GetNowCount() - resultTimeCounter < 1000) {
			// 1秒は表示するようにする
			return;
		}
		else if (Pad::getIns()->get(ePad::A) == 1 || Pad::getIns()->get(ePad::start) == 1) {
			// AボタンまたはSTARTでメニューに戻る
			sozaiManager.clearAll();
			Parameter parameter;
			_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, true);
		}
	}
}

void SceneJudgeGame::draw() const {
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 255), TRUE);

	// ノーツと素材を描画する
	if (currentState == eGameState::Ready || currentState == eGameState::Playing) {
		sozaiManager.draw();
		noteManager->draw();
		noteUIManager->draw();
	}

	if (currentState == eGameState::Ready) {
		// カウントダウンテキスト
		int elapsed = GetNowCount() - stateStartTime;

		// 現在の拍を計算
		int currentBeatIndex = static_cast<int>(elapsed / beatDurationMs);
		int displayCount = 4 - currentBeatIndex; // 4, 3, 2, 1 に変換

		if (displayCount > 0 && displayCount <= 4) {
			DrawFormatString(600, 340, GetColor(255, 255, 255), "%d", displayCount);
		}
	}
	else if (currentState == eGameState::Playing) {
		// スコア描画
		if (noteManager) {
			DrawFormatString(520, 600, GetColor(255, 255, 255), "COMBO: %d", noteManager->getCombo());
			DrawFormatString(20, 70, GetColor(255, 255, 255), "PERFECT: %d", noteManager->getPerfectCount());
			DrawFormatString(20, 120, GetColor(255, 255, 255), "GREAT:   %d", noteManager->getGreatCount());
			DrawFormatString(20, 170, GetColor(255, 255, 255), "GOOD:    %d", noteManager->getGoodCount());
			DrawFormatString(20, 220, GetColor(255, 255, 255), "MISS:    %d", noteManager->getMissCount());
		}
	}
	else if (currentState == eGameState::Result) {
		// リザルト画面
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawFormatString(500, 150, GetColor(255, 255, 0), "RESULT");
		DrawFormatString(500, 250, GetColor(255, 255, 255), "PERFECT : %d", noteManager->getPerfectCount());
		DrawFormatString(500, 300, GetColor(255, 255, 255), "GREAT   : %d", noteManager->getGreatCount());
		DrawFormatString(500, 350, GetColor(255, 255, 255), "GOOD    : %d", noteManager->getGoodCount());
		DrawFormatString(500, 400, GetColor(255, 255, 255), "MISS    : %d", noteManager->getMissCount());

		if (GetNowCount() % 1000 < 500) {
			DrawFormatString(420, 550, GetColor(200, 200, 200), "Press A Button to Return");
		}
	}
}

void SceneJudgeGame::registerActions() {
	// ここで譜面のアクションを登録する(リズムに合わせた素材の切り替えとか、背景変化とか)
}
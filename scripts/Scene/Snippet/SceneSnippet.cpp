#include "SceneSnippet.h"
#include "System/AbstractScene.h"
#include "SnippetGameManager.h"
#include "Common/Sound.h"
#include "System/Pad.h"
#include "System/Define.h"
#include "Action/SetActiveAction.h"
#include "Action/SetWindowAction.h"
#include "Action/EnemyAttackAction.h"
#include "Action/EnemyDefeatAction.h"
#include "StatusWindowManager.h"

using namespace std;

const char* SceneSnippet::ParameterTagStage = "ParameterTagStage";
const char* SceneSnippet::ParameterTagLevel = "ParameterTagLevel";

SceneSnippet::SceneSnippet(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	ChangeFont("Mother3Message");
	SetFontSpace(1);
	SetFontSize(9);
	SetFontThickness(1);
	musicNumber = 0;
	//// サウンド、イメージ、ゲームマネージャーのインスタンスを生成
	snippetGameManager = make_shared<SnippetGameManager>();
	snippetSound = make_shared<SnippetSound>();
	snippetImage = make_shared<SnippetImage>();
	popUpManager = make_shared<PopupNumberManager>(snippetGameManager, snippetImage);
	// 各種オブジェクトのインスタンス設定
	statusManager = make_shared<StatusWindowManager>();
	_statusWindowA = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowB = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowC = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowD = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	statusManager->AddWindow(_statusWindowA);
	statusManager->AddWindow(_statusWindowB);
	statusManager->AddWindow(_statusWindowC);
	statusManager->AddWindow(_statusWindowD);
	messageWindow = new MessageWindow(snippetGameManager, snippetImage);
	playerManager = make_shared<PlayerCharacterManager>();
	PlayerCharacter* playerA = new PlayerCharacter(snippetGameManager, snippetSound, popUpManager);
	PlayerCharacter* playerB = new PlayerCharacter(snippetGameManager, snippetSound, popUpManager);
	PlayerCharacter* playerC = new PlayerCharacter(snippetGameManager, snippetSound, popUpManager);
	PlayerCharacter* playerD = new PlayerCharacter(snippetGameManager, snippetSound, popUpManager);
	playerManager->AddPlayer(playerA);
	playerManager->AddPlayer(playerB);
	playerManager->AddPlayer(playerC);
	playerManager->AddPlayer(playerD);

	enemyManager = new EnemyManager(snippetGameManager, snippetImage, snippetSound, playerManager, statusManager);
	_backImage = make_shared<BackImage>();
	_backImage->SetGameManager(snippetGameManager);
	_backImage->SetImage(snippetImage);
	beatManager = new BeatManager();
	beatManager->SetSound(snippetSound);
	initCharacter();
	setEnemyInstancetToCharacter();
	initWindow();
	bpmManager.setBPM(165);
	beatManager->startMusic(musicNumber);
	bpmManager.startMusic(snippetSound->getBackgroundMusic()[musicNumber]);;

	initEventSystem();
}


void SceneSnippet::update() {

	double beat = bpmManager.getCurrentBeatNum();
	for (auto& e : events) {
		e.update(beat);
	}

	beatManager->update();
	snippetGameManager->proceedTurn();
	popUpManager->update();
	playerManager->getPlayerById(0)->update();
	playerManager->getPlayerById(1)->update();
	playerManager->getPlayerById(2)->update();
	playerManager->getPlayerById(3)->update();
	enemyManager->update();
	_statusWindowA->update();
	_statusWindowB->update();
	_statusWindowC->update();
	_statusWindowD->update();
	messageWindow->update();
	_backImage->update();

	if (Pad::getIns()->get(ePad::start) == 1) {
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(snippetSound->getBackgroundMusic()[musicNumber]);
		snippetGameManager->initBattle();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
		SetUseCharCodeFormat(DX_CHARCODEFORMAT_SHIFTJIS);
		return;
	}
}

void SceneSnippet::draw() const {
	// 一度ドットバイドットの描画
	SetDrawScreen(snippetImage->getScreenHandle());
	_backImage->draw();
	beatManager->draw();
	enemyManager->draw();
	_backImage->drawSecond();
	playerManager->getPlayerById(0)->draw();
	playerManager->getPlayerById(1)->draw();
	playerManager->getPlayerById(2)->draw();
	playerManager->getPlayerById(3)->draw();
	_statusWindowA->draw();
	_statusWindowB->draw();
	_statusWindowC->draw();
	_statusWindowD->draw();
	popUpManager->draw();
	messageWindow->draw();
	enemyManager->drawSecond();
	// 倍率を設定して描画
	SetDrawScreen(DX_SCREEN_BACK);
	int screenRate = 4;
	DrawExtendGraph(0, 0, (Define::WIN_W * screenRate), (Define::WIN_H * screenRate), snippetImage->getScreenHandle(), FALSE);
}


void SceneSnippet::initWindow() {
	_statusWindowA->setPlayerCharacterInstance(playerManager->getPlayerById(0));
	_statusWindowB->setPlayerCharacterInstance(playerManager->getPlayerById(1));
	_statusWindowC->setPlayerCharacterInstance(playerManager->getPlayerById(2));
	_statusWindowD->setPlayerCharacterInstance(playerManager->getPlayerById(3));
	_statusWindowA->setWindowPos(0);
	_statusWindowB->setWindowPos(2);
	_statusWindowC->setWindowPos(4);
	_statusWindowD->setWindowPos(6);
	_statusWindowA->setHP(playerManager->getPlayerById(0)->getHP());
	_statusWindowB->setHP(playerManager->getPlayerById(1)->getHP());
	_statusWindowC->setHP(playerManager->getPlayerById(2)->getHP());
	_statusWindowD->setHP(playerManager->getPlayerById(3)->getHP());
	_statusWindowA->setPP(playerManager->getPlayerById(0)->getPP());
	_statusWindowB->setPP(playerManager->getPlayerById(1)->getPP());
	_statusWindowC->setPP(playerManager->getPlayerById(2)->getPP());
	_statusWindowD->setPP(playerManager->getPlayerById(3)->getPP());
	_statusWindowA->setName();
	_statusWindowB->setName();
	_statusWindowC->setName();
	_statusWindowD->setName();
}

void SceneSnippet::initEventSystem() {
	registerActions();
	events = EventLoader::loadFromFile(
		"Assets/Score/action/snippet.json",
		registry
	);
}

void SceneSnippet::registerActions() {

	registry.registerAction("set_active",
		[this](const nlohmann::json& j) {
			int target = j["target"];
			bool flag = j["flag"];

			PlayerCharacter* p = playerManager->getPlayerById(target);

			return std::make_unique<SetActiveAction>(p, flag);
		}
	);

	registry.registerAction("set_window",
		[this](const nlohmann::json& j) {
			int soundType = 0;
			std::string msg = j["message"];
			if (j.contains("sound")) {
				soundType = j["sound"];
			}


			return std::make_unique<SetWindowAction>(messageWindow, msg, soundType, snippetSound);
		}
	);

	registry.registerAction("set_enemy_attack",
		[this](const nlohmann::json& j) {
			int enemyIndex = j["enemy"];
			Enemy* e = enemyManager->getEnemyIns(enemyIndex);

			if (j.contains("flash")) {
				// フラッシュだけ
				return std::make_unique<EnemyAttackAction>(e, true);
			}

			int soundIndex = j["sound"];
			int damage = j["damage"];
			int targetPlayerId = j["target"];


			return std::make_unique<EnemyAttackAction>(e, soundIndex, damage, targetPlayerId);
		}
	);

	registry.registerAction("set_enemy_defeat",
		[this](const nlohmann::json& j) {
			int enemyIndex = j["enemy"];
			bool finalBossflag = j["is_boss"];
			int nextEnemyId = j["next_id"];

			Enemy* e = enemyManager->getEnemyIns(enemyIndex);

			return std::make_unique<EnemyDefeatAction>(e, finalBossflag, nextEnemyId, snippetSound);
		}
	);
}

void SceneSnippet::initCharacter() {
	playerManager->getPlayerById(0)->setHP(120);
	playerManager->getPlayerById(0)->setPP(00);
	playerManager->getPlayerById(0)->setName(0, 41);
	playerManager->getPlayerById(0)->setName(1, 82);
	playerManager->getPlayerById(0)->setName(2, 5);
	playerManager->getPlayerById(0)->setInstrumentNumber(0);
	playerManager->getPlayerById(0)->setCharacterId(0);
	playerManager->getPlayerById(0)->setMyTurn(0);
	playerManager->getPlayerById(0)->setCharacterId(0);
	playerManager->getPlayerById(0)->setMessageWindow(messageWindow);
	playerManager->getPlayerById(1)->setHP(160);
	playerManager->getPlayerById(1)->setPP(0);
	playerManager->getPlayerById(1)->setName(0, 7);
	playerManager->getPlayerById(1)->setName(1, 30);
	playerManager->getPlayerById(1)->setName(2, 19);
	playerManager->getPlayerById(1)->setName(3, 40);
	playerManager->getPlayerById(1)->setMyTurn(3);
	playerManager->getPlayerById(1)->setInstrumentNumber(1);
	playerManager->getPlayerById(1)->setCharacterId(1);
	playerManager->getPlayerById(1)->setMessageWindow(messageWindow);
	playerManager->getPlayerById(2)->setHP(250);
	playerManager->getPlayerById(2)->setPP(0);
	playerManager->getPlayerById(2)->setName(0, 60);
	playerManager->getPlayerById(2)->setName(1, 12);
	playerManager->getPlayerById(2)->setName(2, 15);
	playerManager->getPlayerById(2)->setName(3, 89);
	playerManager->getPlayerById(2)->setMyTurn(1);
	playerManager->getPlayerById(2)->setInstrumentNumber(2);
	playerManager->getPlayerById(2)->setCharacterId(2);
	playerManager->getPlayerById(2)->setMessageWindow(messageWindow);
	playerManager->getPlayerById(3)->setHP(150);
	playerManager->getPlayerById(3)->setPP(0);
	playerManager->getPlayerById(3)->setName(0, 69);
	playerManager->getPlayerById(3)->setName(1, 21);
	playerManager->getPlayerById(3)->setName(2, 89);
	playerManager->getPlayerById(3)->setMyTurn(2);
	playerManager->getPlayerById(3)->setInstrumentNumber(3);
	playerManager->getPlayerById(3)->setCharacterId(3);
	playerManager->getPlayerById(3)->setMessageWindow(messageWindow);
}

void SceneSnippet::setEnemyInstancetToCharacter() {
	playerManager->getPlayerById(0)->setBeatManager(beatManager);
	playerManager->getPlayerById(0)->setEnemyManagerInstance(enemyManager);
	playerManager->getPlayerById(1)->setBeatManager(beatManager);
	playerManager->getPlayerById(1)->setEnemyManagerInstance(enemyManager);
	playerManager->getPlayerById(2)->setBeatManager(beatManager);
	playerManager->getPlayerById(2)->setEnemyManagerInstance(enemyManager);
	playerManager->getPlayerById(3)->setBeatManager(beatManager);
	playerManager->getPlayerById(3)->setEnemyManagerInstance(enemyManager);
}
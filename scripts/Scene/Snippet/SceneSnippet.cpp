#include "SceneSnippet.h"
#include "System/AbstractScene.h"
#include "SnippetGameManager.h"
#include "Common/Sound.h"
#include "System/Pad.h"
#include "System/Define.h"

using namespace std;

const char* SceneSnippet::ParameterTagStage = "ParameterTagStage";
const char* SceneSnippet::ParameterTagLevel = "ParameterTagLevel";

SceneSnippet::SceneSnippet(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	ChangeFont("Mother3Message");
	SetFontSpace(1);
	SetFontSize(9);
	SetFontThickness(1);
	musicNumber = 0;
	//// サウンド、イメージ、ゲームマネージャーのインスタンスを生成
	snippetGameManager = make_shared<SnippetGameManager>();
	snippetSound = make_shared<SnippetSound>();
	snippetImage = make_shared<SnippetImage>();
	// 各種オブジェクトのインスタンス設定
	_statusWindowA = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowB = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowC = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	_statusWindowD = make_shared<StatusWindow>(snippetGameManager, snippetImage);
	messageWindow = new MessageWindow(snippetGameManager, snippetImage);
	playerA = new PlayerCharacter(snippetGameManager, snippetSound);
	playerB = new PlayerCharacter(snippetGameManager, snippetSound);
	playerC = new PlayerCharacter(snippetGameManager, snippetSound);
	playerD = new PlayerCharacter(snippetGameManager, snippetSound);
	enemyManager = new EnemyManager(snippetGameManager, snippetImage, snippetSound);
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
	beatManager->update();
	snippetGameManager->proceedTurn();
	playerA->update();
	playerB->update();
	playerC->update();
	playerD->update();
	enemyManager->update();
	_statusWindowA->update();
	_statusWindowB->update();
	_statusWindowC->update();
	_statusWindowD->update();
	messageWindow->update();
	_backImage->update();


	double beat = bpmManager.getCurrentBeatNum();

	for (auto& e : events) {
		e.update(beat);
	}

	if (Pad::getIns()->get(ePad::start) == 1) {
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(snippetSound->getBackgroundMusic()[musicNumber]);
		snippetGameManager->initBattle();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
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
	playerA->draw();
	playerB->draw();
	playerC->draw();
	playerD->draw();
	_statusWindowA->draw();
	_statusWindowB->draw();
	_statusWindowC->draw();
	_statusWindowD->draw();
	messageWindow->draw();
	enemyManager->drawSecond();
	// 倍率を設定して描画
	SetDrawScreen(DX_SCREEN_BACK);
	int screenRate = 4;
	DrawExtendGraph(0, 0, (Define::WIN_W * screenRate), (Define::WIN_H * screenRate), snippetImage->getScreenHandle(), FALSE);
}

PlayerCharacter* SceneSnippet::getPlayerById(int id) {
	switch (id) {
	case 0: return playerA;
	case 1: return playerB;
	case 2: return playerC;
	case 3: return playerD;
	default: return nullptr;
	}
}

void SceneSnippet::initWindow() {
	_statusWindowA->setPlayerCharacterInstance(playerA);
	_statusWindowB->setPlayerCharacterInstance(playerB);
	_statusWindowC->setPlayerCharacterInstance(playerC);
	_statusWindowD->setPlayerCharacterInstance(playerD);
	_statusWindowA->setWindowPos(0);
	_statusWindowB->setWindowPos(2);
	_statusWindowC->setWindowPos(4);
	_statusWindowD->setWindowPos(6);
	_statusWindowA->setHP(playerA->getHP());
	_statusWindowB->setHP(playerB->getHP());
	_statusWindowC->setHP(playerC->getHP());
	_statusWindowD->setHP(playerD->getHP());
	_statusWindowA->setPP(playerA->getPP());
	_statusWindowB->setPP(playerB->getPP());
	_statusWindowC->setPP(playerC->getPP());
	_statusWindowD->setPP(playerD->getPP());
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

			PlayerCharacter* p = getPlayerById(target);

			return std::make_unique<SetActiveAction>(p, flag);
		}
	);
}

void SceneSnippet::initCharacter() {
	playerA->setHP(120);
	playerA->setPP(00);
	playerA->setName(0, 41);
	playerA->setName(1, 82);
	playerA->setName(2, 5);
	playerA->setInstrumentNumber(0);
	playerA->setCharacterId(0);
	playerA->setMyTurn(0);
	playerA->setCharacterId(0);
	playerA->setMessageWindow(messageWindow);
	playerB->setHP(160);
	playerB->setPP(0);
	playerB->setName(0, 7);
	playerB->setName(1, 30);
	playerB->setName(2, 19);
	playerB->setName(3, 40);
	playerB->setMyTurn(3);
	playerB->setInstrumentNumber(1);
	playerB->setCharacterId(1);
	playerB->setMessageWindow(messageWindow);
	playerC->setHP(250);
	playerC->setPP(0);
	playerC->setName(0, 60);
	playerC->setName(1, 12);
	playerC->setName(2, 15);
	playerC->setName(3, 89);
	playerC->setMyTurn(1);
	playerC->setInstrumentNumber(2);
	playerC->setCharacterId(2);
	playerC->setMessageWindow(messageWindow);
	playerD->setHP(150);
	playerD->setPP(0);
	playerD->setName(0, 69);
	playerD->setName(1, 21);
	playerD->setName(2, 89);
	playerD->setMyTurn(2);
	playerD->setInstrumentNumber(3);
	playerD->setCharacterId(3);
	playerD->setMessageWindow(messageWindow);
}

void SceneSnippet::setEnemyInstancetToCharacter() {
	playerA->setBeatManager(beatManager);
	playerA->setEnemyManagerInstance(enemyManager);
	playerB->setBeatManager(beatManager);
	playerB->setEnemyManagerInstance(enemyManager);
	playerC->setBeatManager(beatManager);
	playerC->setEnemyManagerInstance(enemyManager);
	playerD->setBeatManager(beatManager);
	playerD->setEnemyManagerInstance(enemyManager);
}
#pragma once
#include <vector>
#include <string>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/Online/WSClient.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct NetPlayer {
	std::string id;

	float x = 0.5f;   // 0〜1
	float y = 0.5f;   // 0〜1
	float accel = 0.0f;

	float heat = 0.0f;
};

class SceneRobot : public AbstractScene
{
public:
	SceneRobot(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneRobot() = default;
	void update() override;
	void draw() const override;
private:
	void setKey();
	void updatePlayers(const json& data);
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	WSClient ws;
	std::atomic<bool> wsConnection = false;
	std::vector<NetPlayer> players;

	std::unordered_map<int, int> sozaiHandles;

	int sampleImg;

	bool gbFlag = false;
};


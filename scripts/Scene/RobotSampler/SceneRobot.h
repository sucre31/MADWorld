#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/Online/WSClient.h"
#include "Common/Online/WSDataHolder.h"

struct RenderPlayer {
	std::string id;

	float x, y;          // 表示位置（補間後）
	float targetX, targetY; // サーバー位置
	float accel;
	float targetAccel;

	float lastSeenTime;
};

class SceneRobot : public AbstractScene
{
public:
	SceneRobot(IOnSceneChangedListener* impl, const Parameter& parameter);
	~SceneRobot() = default;
	void update() override;
	void draw() const override;
private:
	float getTimeSec();
	void setKey();
	SozaiManager sozaiManager;
	NoteManager noteManager;
	MusicManager musicManager;
	PauseMenu pauseMenu;

	WSDataHolder wsHolder;
	std::atomic<bool> wsConnection = false;
	std::vector<NetPlayer> players;
	std::unordered_map<std::string, RenderPlayer> renderPlayers;

	std::unordered_map<int, int> sozaiHandles;
	std::unordered_set<std::string> aliveIds;

	int sampleImg;

	bool gbFlag = false;
};


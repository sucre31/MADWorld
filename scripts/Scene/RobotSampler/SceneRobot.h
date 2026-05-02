#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/PauseMenu.h"
#include "Common/GameObject/NoteManager.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/Online/WSClient.h"
#include "Common/Online/WSDataHolder.h"
#include "Common/Particle.h"


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
	~SceneRobot();
	void update() override;
	void draw() const override;
	void updateParticles(float dt);
private:
	void setMidiKey(int mode);
	float getTimeSec();
	void setKey();
	void captureLoop();
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

	std::unordered_map<std::string, ParticleEmitter> emitters;

	std::vector<eMidi> switchMidi;

	int imgSmall;
	int imgMiddle;
	int imgBig;

	int camLogCounter = 0;
	BASEIMAGE cvBaseImage;
	cv::VideoCapture cap;
	cv::Mat frame;
	unsigned char* cvBuffer = nullptr;
	int cvGraph = -1;

	

	std::thread captureThread;
	std::atomic<bool> runThread;
	std::atomic<bool> hasNewFrame;
	std::mutex frameMutex;
	cv::Mat threadFrame; // スレッドから渡される最新フレーム
	int siHandle = -1;   // ソフトイメージハンドル

	bool gbFlag = false;
};


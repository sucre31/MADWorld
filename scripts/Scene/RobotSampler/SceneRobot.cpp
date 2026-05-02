#include <Dxlib.h>
#include "SceneRobot.h"
#include "System/FpsControl.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;


SceneRobot::SceneRobot(IOnSceneChangedListener* impl, const Parameter& parameter)
	:AbstractScene(impl, parameter),
	noteManager(140, 4, &sozaiManager)
{
	std::vector<std::string> paths = {
	"humanBass",
	"makeLoveSnea",
	"steamHihat",
	"daFunkSnea",
	"workIt",
	"harderBass",
	"oneMoreLoop",
	"getFar",
	"daFunCmon",
	"technologic",
	"all",
	"human",
	"superHero",
	"OnOff",
	"aroundTheWorld",
	"contact",
	"humanSnea"
	};

	// Midi設定
	MIDI::getIns()->openMidi(0, 0);

	std::vector<eMidi> midiKeys = {
	eMidi::C_0, eMidi::F_0, eMidi::E_0, eMidi::D_0,
	eMidi::C_4, eMidi::C_8, eMidi::E_1, eMidi::F_1,
	eMidi::G_0, eMidi::D_S1, eMidi::A_S0, eMidi::F_S0,
	eMidi::C_S1, eMidi::F_S0, eMidi::F_S1, eMidi::A_S0
	};

	switchMidi.push_back(eMidi::A_7);
	switchMidi.push_back(eMidi::A_S7);
	switchMidi.push_back(eMidi::B_7);

	int gridW = 4;
	int gridH = 4;

	int topOffset = 30;
	int bottomOffset = 100;
	int leftOffset = 330;
	int rightOffset = 330;


	double cellW = (Define::WIN_W - leftOffset - rightOffset) / (double)gridW;
	double cellH = (Define::WIN_H - topOffset - bottomOffset) / (double)gridH;

	std::string bassPngPath = "Assets/Sprites/images/robotSampler/";
	std::string bassMoviePath = "Assets/Sprites/movie/robotSampler/";

	for (int y = 0; y < gridH; y++) {
		for (int x = 0; x < gridW; x++) {
			
			int index = y * gridW + x;

			double posX = leftOffset + cellW * (x + 0.5);
			double posY = topOffset + cellH * ((gridH - 1 - y) + 0.5);


			sozaiHandles[index] = 
				sozaiManager.makeSozai(
					"",
					(bassPngPath + paths[index] + ".png").c_str(),
					posX,
					posY
				);
			sozaiManager.addSound(sozaiHandles[index], "");
			sozaiManager.addSprite(sozaiHandles[index], 1, (bassMoviePath + paths[index] + ".avi").c_str());

			sozaiManager.setSozaiMidiKey(
				index,
				midiKeys[index],
				1,
				0
			);
		}
	}

	// humanSnea用の設定
	double posX = leftOffset + cellW * (1 + 0.5);
	double posY = topOffset + cellH * ((gridH - 1) + 0.5);


	sozaiHandles[16] =
		sozaiManager.makeSozai(
			"",
			(bassPngPath + paths[16] + ".png").c_str(),
			posX,
			posY
		);
	sozaiManager.addSound(sozaiHandles[16], "");
	sozaiManager.addSprite(sozaiHandles[16], 1, (bassMoviePath + paths[16] + ".avi").c_str());

	sozaiManager.setSozaiMidiKey(
		16,
		midiKeys[3],
		1,
		0
	);



	// OpenCVカメラ初期化テスト
	cap.open(0, cv::CAP_DSHOW);


	if (!cap.isOpened())
	{
		//printfDx("OpenCV CAMERA OPEN FAILED\n");
	}
	else
	{
		//printfDx("OpenCV CAMERA OPEN OK\n");
	}

	cv::Mat tmp;

	// サイズ固定（重要）
	cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

	// DxLib用バッファ確保
	cvBuffer = new unsigned char[1280 * 720 * 3];

	memset(&cvBaseImage, 0, sizeof(BASEIMAGE));
	CreateFullColorData(&cvBaseImage.ColorData);


	cvBaseImage.GraphData = cvBuffer;
	cvBaseImage.Width = 1280;
	cvBaseImage.Height = 720;
	cvBaseImage.Pitch = 1280 * 3;
	cvBaseImage.MipMapCount = 0;

	runThread = true;
	captureThread = std::thread(&SceneRobot::captureLoop, this);

	// ベースの追加設定
	sozaiManager.setSozaiMidiKey(4, eMidi::A_S3, 1, 0);
	sozaiManager.setSozaiMidiKey(5, eMidi::C_4, 1, 1);
	sozaiManager.setSozaiMidiKey(5, eMidi::D_4, 1, 1);
	sozaiManager.setSozaiMidiKey(5, eMidi::E_4, 1, 1);
	
	for (auto& p : sozaiHandles) {
		sozaiManager.setSozaiEx(p.second, (1.5 / 4.0));
		sozaiManager.setSozaiLayer(p.second, 1);
		sozaiManager.setReverseFlag(p.second, true);
	}

	setMidiKey(0);

	wsHolder.start();

	imgSmall = Image::getIns()->loadSamples("Assets/Sprites/images/particle/lightBig.png");
	imgMiddle = Image::getIns()->loadSamples("Assets/Sprites/images/particle/lightMiddle.png");
	imgBig = Image::getIns()->loadSamples("Assets/Sprites/images/particle/lightSmall.png");
}

SceneRobot::~SceneRobot() {
	if (cvBuffer)
	{
		delete[] cvBuffer;
		cvBuffer = nullptr;
	}

	runThread = false;
	if (captureThread.joinable())
	{
		captureThread.join();
	}

	cap.release();
}


// ESX-1に合わせて素材の設定
void SceneRobot::setMidiKey(int mode) {
	std::vector<eMidi> midiKeys = {
	eMidi::C_0, eMidi::F_0, eMidi::E_0, eMidi::D_0,
	eMidi::C_4, eMidi::C_8, eMidi::E_1, eMidi::F_1,
	eMidi::G_0, eMidi::D_S1, eMidi::A_S0, eMidi::F_S0,
	eMidi::C_S1, eMidi::F_S0, eMidi::F_S1, eMidi::A_S0
	};

	int gridW = 4;
	int gridH = 4;

	switch (mode) {
	case 0:
		// 最初
		sozaiManager.setSozaiLayer(16, 1);
		for (int y = 0; y < gridH; y++) {
			for (int x = 0; x < gridW; x++) {
				int index = y * gridW + x;

				sozaiManager.resetMidiKey(index);

				if (index == 3) {
					continue;
				}

				sozaiManager.setSozaiMidiKey(
					index,
					midiKeys[index],
					1,
					0
				);
			}
		}
		break;

	case 1:
		sozaiManager.setSozaiLayer(16, -1);
		// OnOffなど有効化
		for (int y = 0; y < gridH; y++) {
			for (int x = 0; x < gridW; x++) {

				int index = y * gridW + x;
				sozaiManager.resetMidiKey(index);

				if (index == 10 || index == 11) {
					continue;
				}

				sozaiManager.setSozaiMidiKey(
					index,
					midiKeys[index],
					1,
					0
				);
			}
		}
		break;

	case 2:
		// human after all有効化
		sozaiManager.setSozaiLayer(16, -1);
		for (int y = 0; y < gridH; y++) {
			for (int x = 0; x < gridW; x++) {

				int index = y * gridW + x;

				sozaiManager.resetMidiKey(index);

				if (index == 12 || index == 15) {
					continue;
				}

				sozaiManager.setSozaiMidiKey(
					index,
					midiKeys[index],
					1,
					0
				);
			}
		}
		break;
	}

	// ベースの追加設定
	sozaiManager.setSozaiMidiKey(4, eMidi::A_S3, 1, 0);
	sozaiManager.setSozaiMidiKey(5, eMidi::C_4, 1, 1);
	sozaiManager.setSozaiMidiKey(5, eMidi::D_4, 1, 1);
	sozaiManager.setSozaiMidiKey(5, eMidi::E_4, 1, 1);
}

void SceneRobot::update() {
	wsHolder.update();
	players = wsHolder.getPlayers();


	if (gbFlag && hasNewFrame.exchange(false))
	{
		cv::Mat local;

		{
			std::lock_guard<std::mutex> lock(frameMutex);
			local = threadFrame.clone();
		}

		if (!local.empty())
		{
			memcpy(cvBuffer, local.data, 1280 * 720 * 3);

			if (cvGraph == -1)
			{
				cvGraph = CreateGraphFromBaseImage(&cvBaseImage);
			}
			else
			{
				ReCreateGraphFromBaseImage(&cvBaseImage, cvGraph);
			}
		}
	}


	float now = getTimeSec();

	aliveIds.clear();

	float dt = FpsControl::getIns()->getDeltaTime();

	for (auto& p : players)
	{
		aliveIds.insert(p.id);

		auto& r = renderPlayers[p.id];
		r.id = p.id;
		r.targetX = p.x;
		r.targetY = p.y;
		r.targetAccel = p.accel;
		r.lastSeenTime = now;

		r.x += (r.targetX - r.x) * 0.2f;
		r.y += (r.targetY - r.y) * 0.2f;
		r.accel += (r.targetAccel - r.accel) * 0.3f;

		if (emitters.find(p.id) == emitters.end()) {
			emitters[p.id] = ParticleEmitter();
		}
	}

	const float DEAD_TIME = 2.0f; // 2秒無通信で消す

	for (auto it = renderPlayers.begin(); it != renderPlayers.end(); )
	{
		float diff = now - it->second.lastSeenTime;

		if (diff > DEAD_TIME)
		{
			it = renderPlayers.erase(it);
		}
		else
		{
			++it;
		}
	}

	updateParticles(dt);

	sozaiManager.update();
	if (Pad::getIns()->get(ePad::B) == 1) {
		// 背景色変更
		gbFlag = !gbFlag;
	}

	// 素材の切り替え
	if (MIDI::getIns()->get(switchMidi[0]) == 1 || MIDI::getIns()->get(switchMidi[0], 1) == 1) {
		setMidiKey(0);
	}

	if (MIDI::getIns()->get(switchMidi[1]) == 1 || MIDI::getIns()->get(switchMidi[1], 1) == 1) {
		setMidiKey(1);
	}

	if (MIDI::getIns()->get(switchMidi[2]) == 1 || MIDI::getIns()->get(switchMidi[2], 1) == 1) {
		setMidiKey(2);
	}


	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::TitleLive, parameter, stackClear);
		return;
	}
}

void SceneRobot::updateParticles(float dt)
{
	for (auto& [id, r] : renderPlayers)
	{
		auto it = emitters.find(id);
		if (it == emitters.end()) continue;

		float accel = r.accel;

		auto& emitter = it->second;
		emitter.setPosition(r.x * Define::WIN_W,
			r.y * Define::WIN_H);
		emitter.update(dt, accel);
	}
}

float SceneRobot::getTimeSec()
{
	return (float)GetNowCount() / 1000.0f;
}

void SceneRobot::captureLoop()
{
	while (runThread)
	{
		cv::Mat frameLocal;

		cap >> frameLocal;
		if (frameLocal.empty()) continue;

		cv::flip(frameLocal, frameLocal, 1);
		//cv::cvtColor(frameLocal, frameLocal, cv::COLOR_BGR2RGB);

		{
			std::lock_guard<std::mutex> lock(frameMutex);
			threadFrame = frameLocal.clone();
		}

		hasNewFrame = true;
	}
}

void SceneRobot::draw() const {
	if (gbFlag)
	{
		if (cvGraph != -1)
		{
			DrawRotaGraph(Define::WIN_W / 2, Define::WIN_H / 2, 1.0, 0, cvGraph, FALSE, TRUE);
		}
	}

	for (const auto& [id, r] : renderPlayers)
	{
		int x = (int)(r.x * Define::WIN_W);
		int y = (int)(r.y * Define::WIN_H);

		auto it = emitters.find(id);
		if (it == emitters.end()) continue;

		it->second.draw(imgSmall, imgMiddle, imgBig);
	}
	sozaiManager.draw();
}

void SceneRobot::setKey() {
}
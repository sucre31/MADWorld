#include <DxLib.h>
#include "SceneAlice.h"
#include "Common/Sound.h"
#include "Common/Image.h"
#include "System/Define.h"
#include "System/Keyboard.h"
#include "System/Pad.h"
#include "System/FpsControl.h"


SceneAlice::SceneAlice(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample0.wav", "Assets/sprites/movie/Alice/Samples/AliceSample0.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample1.wav", "Assets/sprites/movie/Alice/Samples/AliceSample1.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample2.wav", "Assets/sprites/movie/Alice/Samples/AliceSample0.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample3.wav", "Assets/sprites/movie/Alice/Samples/AliceSample3.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample4.wav", "Assets/sprites/movie/Alice/Samples/AliceSample4.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample5.wav", "Assets/sprites/movie/Alice/Samples/AliceSample5.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample6.wav", "Assets/sprites/movie/Alice/Samples/AliceSample6.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample7.wav", "Assets/sprites/movie/Alice/Samples/AliceSample7.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample8.wav", "Assets/sprites/movie/Alice/Samples/AliceSample8.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample9.wav", "Assets/sprites/movie/Alice/Samples/AliceSample9.avi", 640, 360);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample11.wav", "Assets/sprites/movie/Alice/Samples/AliceSample11.avi", 0, 0);
	sozaiManager.makeSozai("Assets/Sounds/Alice/AliceSample12.wav", "Assets/sprites/movie/Alice/Samples/AliceSample12.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample12.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample13.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample14.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample15.avi", 0, 0);
	sozaiManager.setSozaiKey(0, ePad::L, 0);
	sozaiManager.setSozaiKey(1, ePad::down, 0);
	sozaiManager.setSozaiKey(2, ePad::R, 0);
	sozaiManager.setSozaiKey(3, ePad::left, 0);
	sozaiManager.setSozaiKey(4, ePad::A, 0);
	sozaiManager.setSozaiKey(5, ePad::up, 0);
	sozaiManager.setSozaiKey(6, ePad::X, 0);
	sozaiManager.setSozaiKey(7, ePad::right, 0);
	sozaiManager.setSozaiKey(8, ePad::B, 0);
	sozaiManager.setSozaiKey(9, ePad::Y, 0);
	sozaiManager.setSozaiKey(10, ePad::ZL, 0);
	sozaiManager.setSozaiKey(11, ePad::ZR, 0);
	isMusicPlay = false;
	for (int i = 0; i < 10; i++) {
		sozaiManager.setSozaiEx(i, 0.25);
		sozaiManager.setSozaiPos(i, 160 + (i % 4) * 320, 90 + (i / 4) * 180);
	}
	aliceDrumHandle = Sound::getIns()->loadSamples("Assets/Sounds/Alice/drumNBass.wav");

	camera.start(0, 1280, 720);
	wsHolder.start();


	imgSmall = Image::getIns()->loadSamples("Assets/Sprites/images/particle/circleMiddle.png");
	imgMiddle = Image::getIns()->loadSamples("Assets/Sprites/images/particle/circleBig.png");
	imgBig = Image::getIns()->loadSamples("Assets/Sprites/images/particle/circleSmall.png");
}

SceneAlice::~SceneAlice() {
	camera.stop();
}

void SceneAlice::update() {
	wsHolder.update();
	players = wsHolder.getPlayers();

	sozaiManager.update();
	camera.update();
	if (Pad::getIns()->get(ePad::change) == 1) {
		if (isMusicPlay) {
			isMusicPlay = false;
			StopSoundMem(aliceDrumHandle);
		}
		else {
			isMusicPlay = true;
			PlaySoundMem(aliceDrumHandle, DX_PLAYTYPE_LOOP, TRUE);
		}
	}

	float now = (float)GetNowCount() / 1000.0f;

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

	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(aliceDrumHandle);
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
		return;
	}
}

void SceneAlice::updateParticles(float dt)
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


void SceneAlice::draw() const {
	int h = camera.getGraphHandle();
	if (h != -1)
	{
		DrawRotaGraph((Define::WIN_W * (7.0 / 8.0)), (Define::WIN_H * (7.0 / 8.0)), 0.25, 0.0, h, FALSE);
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
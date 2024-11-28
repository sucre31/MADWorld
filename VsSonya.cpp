#include <memory>
#include <Dxlib.h>
#include "VsSonya.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "Define.h"
#include "snowBall.h"


VsSonya::VsSonya(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	shiwakeMasterHandle = shiwakeMasterHandle = Sound::getIns()->loadBGM("Assets/Sounds/sonya/shiwakeMaster.wav");
	PlaySoundMem(shiwakeMasterHandle, DX_PLAYTYPE_LOOP, TRUE);
	bpmManager.setBpm(160);
	bpmManager.startMusic();


	sozaiManager.makeSozai("Assets/Sounds/sonya/hey.wav", "Assets/Sprites/images/sonya/yasuna/yasuna0.png", Define::WIN_W * 3 / 4, Define::WIN_H * 3 / 4 - 40);
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna2.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna3.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna4.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna1.png");
	sozaiManager.addSprites(0, "Assets/Sprites/images/sonya/yasuna/yasuna0.png");
	sozaiManager.addSound(0, "Assets/Sounds/sonya/sukiari.wav");
	sozaiManager.addSound(0, "");
	sozaiManager.setReverseFlag(0, false);
	//sozaiManager.setSozaiKey(0, ePad::right, 0);
	//sozaiManager.setSozaiKey(0, ePad::down, 1);
	sozaiManager.setSozaiEx(0, 1.25);
	sozaiManager.setMultiSound(0, true);

	sozaiManager.makeSozai("Assets/Sounds/sonya/tto.wav", "Assets/Sprites/images/sonya/sonya/sonya0.png", Define::WIN_W * 1 / 4, Define::WIN_H * 3 / 4 - 40);
	//sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya1.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya2.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya3.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya4.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya5.png");
	sozaiManager.addSprites(1, "Assets/Sprites/images/sonya/sonya/sonya0.png");
	sozaiManager.setReverseFlag(1, false);
	sozaiManager.setSozaiKey(1, ePad::A, 0);
	sozaiManager.setSozaiEx(1, 0.75);

	// 背景の設定
	sideBarR.setPosX(1120);
	backGround[0].loadBackImage("Assets/Sprites/images/sonya/sky.png");
	backGround[1].loadBackImage("Assets/Sprites/images/sonya/house.png");
	backGround[2].loadBackImage("Assets/Sprites/images/sonya/bush.png");
	backGround[3].loadBackImage("Assets/Sprites/images/sonya/wall.png");
	backGround[4].loadBackImage("Assets/Sprites/images/sonya/denchu.png");

	debugSEHandle = Sound::getIns()->loadSamples("Assets/Sounds/sonya/tto.wav");

	// 譜面の作成 データファイルから読みたい
	addSnowLaunch(100, 0);
	addSnowLaunch(116, 0);
	addSnowLaunch(132, 0);
	addSnowLaunch(144, 1);
	addSnowLaunch(148, 2);
	addSnowLaunch(152, 2);
	addSnowLaunch(164, 0);
	addSnowLaunch(180, 0);
	addSnowLaunch(196, 0);
	addSnowLaunch(208, 0);
	addSnowLaunch(222, 0);
	addSnowLaunch(234, 0);
	addSnowLaunch(250, 0);
	addSnowLaunch(266, 0);
	addSnowLaunch(272, 1);
	addSnowLaunch(276, 2);
	addSnowLaunch(280, 2);
	addSnowLaunch(292, 0);
	addSnowLaunch(308, 0);
	addSnowLaunch(324, 0);
	addSnowLaunch(336, 0);
	addSnowLaunch(348, 0);
	addSnowLaunch(352, 1);
	addSnowLaunch(356, 2);
	addSnowLaunch(360, 2);
	addSnowLaunch(368, 1);
	addSnowLaunch(372, 2);
	addSnowLaunch(376, 2);
	addSnowLaunch(390, 0);
	addSnowLaunch(400, 0);
	addSnowLaunch(412, 0);
	addSnowLaunch(416, 1);
	addSnowLaunch(420, 2);
	addSnowLaunch(424, 2);
	addSnowLaunch(432, 1);
	addSnowLaunch(436, 2);
	addSnowLaunch(440, 2);
	addSnowLaunch(448, 1);
	addSnowLaunch(452, 2);
	addSnowLaunch(456, 2);
	addSnowLaunch(470, 0);
	addSnowLaunch(480, 0);
	addSnowLaunch(492, 0);//
	addSnowLaunch(506, 0);
	addSnowLaunch(512, 1);
	addSnowLaunch(516, 2);
	addSnowLaunch(520, 2);
	addSnowLaunch(532, 0);
	addSnowLaunch(544, 1);
	addSnowLaunch(548, 2);
	addSnowLaunch(552, 2);
	addSnowLaunch(564, 0);
	addSnowLaunch(576, 1);
	addSnowLaunch(580, 2);
	addSnowLaunch(584, 2);
	addSnowLaunch(596, 0);
	addSnowLaunch(608, 1);
	addSnowLaunch(612, 2);
	addSnowLaunch(616, 2);
	addSnowLaunch(630, 0);
	addSnowLaunch(640, 0);
	addSnowLaunch(652, 0);
	addSnowLaunch(662, 0);
	addSnowLaunch(672, 1);
	addSnowLaunch(676, 2);
	addSnowLaunch(680, 2);
	addSnowLaunch(692, 0);
	addSnowLaunch(704, 1);
	addSnowLaunch(708, 2);
	addSnowLaunch(712, 2);
	addSnowLaunch(720, 1);
	addSnowLaunch(724, 2);
	addSnowLaunch(728, 2);

	prevTime = GetNowHiPerformanceCount();

	showBar = true;
	tmp16Beat = 0;
	beatChanged = false;
}

void VsSonya::update() {
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime;

	sozaiManager.update();

	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}

	if (Pad::getIns()->get(ePad::R) == 1) {
		showBar = !showBar;
	}

	double nowBeat = bpmManager.getCurrentBeatNum();

	if (tmp16Beat != (int)(nowBeat * 4)) {
		tmp16Beat = (int)(nowBeat * 4);
		beatChanged = true;
	}

	if (beatChanged) {
		// 16分音符の中に1回だけ処理をするとき
		beatChanged = false;

		for (int i = 0; i < launchList.size(); i++) {
			if (tmp16Beat == launchList[i].beatNum) {
				makeSnowBall(launchList[i].launchType);
			}
		}
	}

	for (int i = 0; i < snowBallPtr.size(); i++) {
		snowBallPtr[i]->update();
		if (snowBallPtr[i]->getState() == 1) {
			// 雪玉hit
			sozaiManager.playSozai(1, 0);
			snowBallPtr[i]->setState(2);
		}
		if (snowBallPtr[i]->getState() == 3) {
			// 雪玉消滅
			snowBallPtr.erase(snowBallPtr.begin() + i);
			i--;
		}
	}
}

/*
@brief 雪玉のインスタンス生成 いちいち作らずに使いまわすべきかも
@param launchType 0:ノーマル 1:隙あり 2:無言(1に続ける)
*/
void VsSonya::makeSnowBall(int launchType) {
	switch (launchType) {
	case 0:
		sozaiManager.playSozai(0, 0);
		break;
	case 1:
		sozaiManager.playSozai(0, 1);
		break;
	case 2:
		sozaiManager.playSozai(0, -1);
		break;
	}
	snowBallPtr.push_back(std::make_unique<snowBall>());
	snowBallPtr[snowBallPtr.size() - 1]->setSEHandle(debugSEHandle);
}

void VsSonya::addSnowLaunch(int beat, int type) {
	launch tmpLaunchData;
	tmpLaunchData.beatNum = beat;
	tmpLaunchData.launchType = type;
	launchList.push_back(tmpLaunchData);
}

void VsSonya::draw() const{
	for (int i = 0; i < backgroundNum; i++) {
		backGround[i].draw();
	}
	sozaiManager.drawSozai(1);
	for (int i = 0; i < snowBallPtr.size(); i++) {
		snowBallPtr[i]->draw();
	}
	sozaiManager.drawSozai(0);
	if (showBar) {
		sideBarL.draw();
		sideBarR.draw();
	}

}
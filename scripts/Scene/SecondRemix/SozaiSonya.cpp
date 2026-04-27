#include "SozaiSonya.h"
#include <Dxlib.h>

SozaiSonya::SozaiSonya() : prevTime(0), prevAvoidTime(0){
	sozaiPads[(int)SonyaSound::Hey] = ePad::MAX;
	sozaiPads[(int)SonyaSound::Tto] = ePad::A;
	sozaiPads[(int)SonyaSound::Sukiari] = ePad::MAX;
	sozaiPads[(int)SonyaSound::Hit] = ePad::MAX;

	sideBarR.setPosX(1120);
}


void SozaiSonya::update(){
	if (isActive) {

		LONGLONG curTime = GetNowHiPerformanceCount();
		LONGLONG deltaTime = curTime - prevTime;

		double nowBeat = bpmManager->getCurrentBeatNum();

		for (int i = 0; i < snowBallPtr.size(); i++) {
			snowBallPtr[i]->update();
			if (snowBallPtr[i]->getState() == stateSnow::CHECK) {
				// 回避タイミング
				if (Pad::getIns()->get(ePad::B) == 1 && avoidFlag == false) {
					// 回避成功
					snowBallPtr[i]->setState(stateSnow::AVOID);
				}
			}
			if (snowBallPtr[i]->getState() == stateSnow::SONYAHIT) {
				// 雪玉ソーニャhit
				sozaiManager->playSozai(sozaiHandles[(int)SonyaSozai::Sonya], 2);
				snowBallPtr[i]->setState(stateSnow::DESTROY);
			}
			if (snowBallPtr[i]->getState() == stateSnow::WALLHIT) {
				// 雪玉壁hit
				snowBallPtr[i]->setState(stateSnow::DESTROY);
			}
			if (snowBallPtr[i]->getState() == stateSnow::KILL) {
				// 雪玉消滅
				snowBallPtr.erase(snowBallPtr.begin() + i);	// 重いらしい
				i--;
			}
		}

		if (Pad::getIns()->get(ePad::A) == 1) {
			if (avoidFlag == false) {
				prevAvoidTime = curTime;
				avoidFlag = true;
			}
		}

		if (curTime - prevAvoidTime > bpmManager->getOneBeatTime() / 2 && avoidFlag == true) {
			avoidFlag = false;
		}
	}
	else {
		for (int i = 0; i < snowBallPtr.size(); i++) {
			snowBallPtr[i]->update();
		}
	}
}

void SozaiSonya::draw() const {
	if (isActive) {
		for (int i = 0; i < snowBallPtr.size(); i++) {
			snowBallPtr[i]->draw();
		}
		sideBarL.draw();
		sideBarR.draw();
	}
}

void SozaiSonya::initSozai() {
	std::string basePath = "Assets/Sprites/images/sonya/";

	sozaiHandles[(int)SonyaSozai::Sonya] =
		sozaiManager->makeSozai("", (basePath + "sonya/sonya0.png").c_str(), (Define::WIN_W * (1.0 / 4.0) + 30), (Define::WIN_H / 2.0) + 110);
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Sonya], "Assets/Sounds/sonya/tto.wav");
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Sonya], "Assets/Sounds/sonya/sonyaHit.wav");

	std::vector<int> nums = { 2, 3, 4, 5, 5, 0 };
	for (int n : nums) {
		std::string path = basePath + "sonya/sonya" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Sonya], 1, path.c_str());
	}

	nums = { 2, 3, 4, 5, 5, 0 };
	for (int n : nums) {
		std::string path = basePath + "sonya/sonya" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Sonya], 2, path.c_str());
	}

	sozaiHandles[(int)SonyaSozai::Yasuna] =
		sozaiManager->makeSozai("", (basePath + "yasuna/yasuna0.png").c_str(), (Define::WIN_W * (3.0 / 4.0)), (Define::WIN_H / 2.0) + 130);
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Yasuna], "Assets/Sounds/sonya/hey.wav");
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Yasuna], "Assets/Sounds/sonya/sukiari.wav");
	sozaiManager->addSound(sozaiHandles[(int)SonyaSozai::Yasuna], "");

	nums = { 1, 2, 3, 4, 1, 0 };
	for (int n : nums) {
		std::string path = basePath + "yasuna/yasuna" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Yasuna], 1, path.c_str());
	}
	for (int n : nums) {
		std::string path = basePath + "yasuna/yasuna" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Yasuna], 2, path.c_str());
	}
	for (int n : nums) {
		std::string path = basePath + "yasuna/yasuna" + std::to_string(n) + ".png";
		sozaiManager->addSprite(sozaiHandles[(int)SonyaSozai::Yasuna], 3, path.c_str());
	}

	sozaiManager->setSozaiEx(sozaiHandles[(int)SonyaSozai::Sonya], 1);
	sozaiManager->setSozaiEx(sozaiHandles[(int)SonyaSozai::Yasuna], 1.3);

	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Sonya], 8);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Yasuna], 8);

	sozaiManager->setMultiSound(sozaiHandles[(int)SonyaSozai::Yasuna], true);

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
	}

	// 背景の設定
	const char* backGroundPaths[] = {
	"Assets/Sprites/images/sonya/sky.png",
	"Assets/Sprites/images/sonya/house.png",
	"Assets/Sprites/images/sonya/bush.png",
	"Assets/Sprites/images/sonya/wall.png",
	"Assets/Sprites/images/sonya/denchu.png",
	"Assets/Sprites/images/sonya/sideBar1.png",
	"Assets/Sprites/images/sonya/sideBar1.png"
	};

	for (int i = 0; i < std::size(backGroundPaths); i++) {
		sozaiHandles[(int)SonyaSozai::Back0 + i] =
			sozaiManager->makeSozai("", backGroundPaths[i], (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
		sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Back0 + i], 1+i);
	}
	sozaiManager->setSozaiPos(sozaiHandles[(int)SonyaSozai::Back5], 1200, (Define::WIN_H / 2.0));
	sozaiManager->setSozaiPos(sozaiHandles[(int)SonyaSozai::Back6], 80, (Define::WIN_H / 2.0));

}

void SozaiSonya::setLayerFront() {
	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Sonya], 6);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Yasuna], 6);

	for (int i = 0; i < 5; i++) {
		sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Back0 + i], 1 + i);
	}
	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Back5], 10);
	sozaiManager->setSozaiLayer(sozaiHandles[(int)SonyaSozai::Back6], 10);
}

void SozaiSonya::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)SonyaSozai::Sonya], sozaiPads[(int)SonyaSound::Tto], 1);
	//sozaiManager->setSozaiKey(sozaiHandles[(int)SonyaSozai::Yasuna], sozaiPads[(int)SonyaSound::Hey], 1);
}

/*
@brief 雪玉のインスタンス生成 いちいち作らずに使いまわすべきかも
@param launchType 0:ノーマル 1:隙あり 2:無言(1に続ける)
*/
void SozaiSonya::makeSnowBall(int launchType) {
	switch (launchType) {
	case 0:
		sozaiManager->playSozai(sozaiHandles[(int)SonyaSozai::Yasuna], 1);
		snowBallPtr.push_back(std::make_unique<snowBall>(132, 1.0, throwType::Normal));
		break;
	case 1:
		sozaiManager->playSozai(sozaiHandles[(int)SonyaSozai::Yasuna], 2);
		snowBallPtr.push_back(std::make_unique<snowBall>(132, 1.5, throwType::PARABOLA));
		break;
	case 2:
		sozaiManager->playSozai(sozaiHandles[(int)SonyaSozai::Yasuna], 3);
		snowBallPtr.push_back(std::make_unique<snowBall>(132, 1.0, throwType::Normal));
		break;
	}
}

void SozaiSonya::addSnowLaunch(int beat, int type) {
	launch tmpLaunchData;
	tmpLaunchData.beatNum = beat;
	tmpLaunchData.launchType = type;
	launchList.push_back(tmpLaunchData);
}

void SozaiSonya::trigger(int actionId) {
	// actionId = 雪玉タイプ
	makeSnowBall(actionId);
}
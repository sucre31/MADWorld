#include <Dxlib.h>
#include "SceneRobot.h"

SceneRobot::SceneRobot(IOnSceneChangedListener* impl, const Parameter& parameter)
	:AbstractScene(impl, parameter),
	noteManager(140, 4, &sozaiManager)
{
	std::vector<std::string> paths = {
	"humanBass",
	"daFunkSnea",
	"steamHihat",
	"makeLoveSnea",
	"workIt",
	"harderBass",
	"oneMoreLoop",
	"getFar",
	"daFunCmon",
	"technologic",
	"all",
	"human",
	"OnOff",
	"superHero",
	"aroundTheWorld",
	"contact",
	};

	// Midi設定
	MIDI::getIns()->openMidi(0, 0);

	std::vector<eMidi> midiKeys = {
	eMidi::C_0, eMidi::D_0, eMidi::E_0, eMidi::F_0,
	eMidi::C_4, eMidi::C_8, eMidi::E_1, eMidi::F_1,
	eMidi::G_0, eMidi::D_S1, eMidi::A_S0, eMidi::F_S0,
	eMidi::F_S0, eMidi::C_S1, eMidi::F_S1, eMidi::C_S1
	};

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
}

void SceneRobot::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::B) == 1) {
		// 背景色変更
		gbFlag = !gbFlag;
	}

	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

void SceneRobot::draw() const {
	if (gbFlag) {
		DrawBox(
			0,
			0,
			Define::WIN_W,
			Define::WIN_H,
			GetColor(0, 255, 0),
			TRUE // 塗りつぶし
		);
	}
	sozaiManager.draw();
}

void SceneRobot::setKey() {
}
#include <DxLib.h>
#include "SceneMainMenu.h"
#include "Sound.h"
#include "Image.h"
#include "Pad.h"
#include "FpsControl.h"

SceneMainMenu::SceneMainMenu(IOnSceneChangedListener* impl, const Parameter& parameter) : validIconNum(0) , selectIconNo(-1), AbstractScene(impl, parameter)
{
	cursorIns.loadCursorImage("Assets/Sprites/images/MainMenu/cursor.png");
	backGround.loadBackImage("Assets/Sprites/images/MainMenu/UISample.png");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	musicHandle = Sound::getIns()->loadSamples("Assets/Sounds/Menu/Menu2.wav");
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, TRUE);

	icon[0].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail1.png");
	icon[1].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail2.png");
	icon[2].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail3.png");
	icon[3].loadThumbnail("Assets/Sprites/images/MainMenu/thumbnail4.png");
	for (int i = 0; i < 4; i++) {
		icon[i].setPos(130, 160 + i * 133);
		icon[i].enableIconFunc(true);
		validIconNum++;
	}
	SetMouseDispFlag(FALSE);	// カーソル非表示
	prevTime = GetNowHiPerformanceCount();
}

void SceneMainMenu::update()
{
	int cursorX, cursorY;
	LONGLONG curTime = GetNowHiPerformanceCount();
	LONGLONG deltaTime = curTime - prevTime;
	prevTime = curTime;
	cursorX = cursorIns.getCursorPosX();
	cursorY = cursorIns.getCursorPosY();
	double speedRate = 2.0 * (deltaTime / 500);
	selectIconNo = -1;
	bool isHit;

	for (int i = 0; i < validIconNum; i++) {
		isHit = icon[i].checkCursorHit(cursorX, cursorY);
		if (isHit) {
			selectIconNo = i;
		}
	}


	if (Pad::getIns()->get(ePad::Y) >= 1) {
		speedRate = 3.0 * (deltaTime / 500);
	}
	if (Pad::getIns()->get(ePad::A) >= 1) {
		// アイコンあればシーンチェンジ
		int sceneNum = getIconScene(selectIconNo);
		if (sceneNum != -1) {
			SetMouseDispFlag(TRUE);
			Parameter parameter;
			StopSoundMem(musicHandle);
			const bool stackClear = true;
			_implSceneChanged->onSceneChanged(eScene(sceneNum), parameter, stackClear);
		}
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		StopSoundMem(musicHandle);
		SetMouseDispFlag(TRUE);
		Parameter parameter;
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
    if (Pad::getIns()->get(ePad::up) >= 1) {
		cursorIns.plusPos(0, -0.1 * speedRate);
    }
	if (Pad::getIns()->get(ePad::down) >= 1) {
		cursorIns.plusPos(0, 0.1 * speedRate);
	}
	if (Pad::getIns()->get(ePad::right) >= 1) {
		cursorIns.plusPos(0.1 * speedRate, 0);
	}
	if (Pad::getIns()->get(ePad::left) >= 1) {
		cursorIns.plusPos(-0.1 * speedRate, 0);
	}
}

void SceneMainMenu::draw() const
{
	backGround.draw();
	for (int i = 0; i < iconNum; i++) {
		icon[i].draw();
	}
	cursorIns.draw();
}

/*
@brief アイコン番号とシーン番号を対応させる
*/
int SceneMainMenu::getIconScene(int iconNum) {
	switch (iconNum) {
	case 0:
		return -1;
	case 1:
		return eScene::LoveSong;
	case 2:
		return eScene::LightPlane;
	case 3:
		return eScene::Alice;
	default:
		return -1;
	}
}
#include <Dxlib.h>
#include "PauseMenu.h"

PauseMenu::PauseMenu() : selectCmd(0) {
	graphHandle = Image::getIns()->loadSamples("Assets/Sprites/images/System/pauseWindow.png");
	seHandle = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/select.wav");
}

void PauseMenu::setActive() {
	activeMenu = true;
	selectCmd = 1;
}

bool PauseMenu::update(){
	if (Pad::getIns()->get(ePad::left) == 1) {
		if (selectCmd == 1) {
			PlaySoundMem(seHandle, DX_PLAYTYPE_BACK, TRUE);
			selectCmd = 0;
		}
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		if (selectCmd == 0) {
			PlaySoundMem(seHandle, DX_PLAYTYPE_BACK, TRUE);
			selectCmd = 1;
		}
	}

	if (Pad::getIns()->get(ePad::start) == 1) {
		// ポーズ解除
		selectCmd = 1;
		activeMenu = false;
	}

	if (Pad::getIns()->get(ePad::A) == 1) {
		// コマンドを確定させる
		activeMenu = false;
	}
	return true;
}

void PauseMenu::draw() const {
	if (activeMenu) {
		int centerX = Define::WIN_W / 2.0;
		int centerY = Define::WIN_H / 2.0;

		DrawRotaGraph(centerX, centerY, 1.0, 0.0, graphHandle, TRUE, FALSE);
		DrawString(centerX - 250, centerY - 100, "メインメニューに\n戻りますか？", GetColor(0, 0, 0));
		DrawString(centerX - 160, centerY + 100, "はい", GetColor(0, 0, 0));
		DrawString(centerX + 100, centerY + 100, "いいえ", GetColor(0, 0, 0));

		if (selectCmd == 0) {
			DrawString(centerX - 200, centerY + 100, "→", GetColor(0, 0, 0));
		}
		else {
			DrawString(centerX + 60, centerY + 100, "→", GetColor(0, 0, 0));
		}
	}
}
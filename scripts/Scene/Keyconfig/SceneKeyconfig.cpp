#include <array>
#include <DxLib.h>
#include "System/Pad.h"
#include "SceneKeyconfig.h"

SceneKeyconfig::SceneKeyconfig(IOnSceneChangedListener* impl, const Parameter& parameter)
	: selectPadNum(0), setKeyChange(false), isWaitingForKeyChange(false), AbstractScene(impl, parameter) {

}

void SceneKeyconfig::update() {

	if (isWaitingForKeyChange) {
		if (Pad::getIns()->get(ePad::A) == 0) {
			// Aボタンが離されたらキー変更待ち状態に移行
			setKeyChange = true;
			isWaitingForKeyChange = false;
		}
		return;
	}

	if (setKeyChange) {
		// キー変更待ち状態の処理
		// ここで新しいキー入力を取得して、対応するePadに割り当てる
		int padInput;
		padInput = GetJoypadInputState(DX_INPUT_PAD1);//パッドの入力状態を取得
		for (int i = 0; i < 16; i++) {
			if (padInput & (1 << i)) {
				// 新しいキー入力があった場合、対応するePadに割り当てる
				Pad::getIns()->SetPadJoint((ePad)selectPadNum, i);
				setKeyChange = false; // キー変更が完了したら待ち状態を解除
				return;
			}
		}
		return;
	}

	if (Pad::getIns()->get(ePad::down) == 1) {
		selectPadNum = (selectPadNum + 1) % 14;
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		selectPadNum = (selectPadNum + 13) % 14;
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		selectPadNum = (selectPadNum + 7) % 14;
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		selectPadNum = (selectPadNum + 7) % 14;
	}

	if (Pad::getIns()->get(ePad::A) == 1) {
		// Aボタンでキー変更待ち状態に移行(離した後に移行する)
		isWaitingForKeyChange = true;
		setKeyChange = false;
	}

	if (Pad::getIns()->get(ePad::B) == 1) {
		// Bボタンで前のシーンに戻る
		Parameter parameter;
		const bool stackClear = true;
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneKeyconfig::draw() const {
	static constexpr std::array<const char*, 14> buttonNames = {
	"Down", "Left", "Right", "Up", "A", "B", "Y", "X",
	"L", "R", "ZR", "ZL", "Start", "Change"
	};

	if (setKeyChange) {
		DrawFormatString(100, 50, GetColor(255, 0, 0), "キー変更待機中... 新しいキーを押してください");
	}
	else {
		DrawFormatString(100, 50, GetColor(255, 255, 255), "キー設定画面");
	}

	for (int i = 0; i < 14; i++) {
		int xPos = 100 + (i / 7) * 500;
		int yPos = 100 + (i % 7) * 60;

		DrawFormatString(xPos, yPos, GetColor(255, 255, 255), buttonNames[i]);
		DrawFormatString(xPos + 200, yPos, GetColor(255, 255, 255), "%d番", Pad::getIns()->GetPadJoint((ePad)i));
		if (i == selectPadNum) {
			DrawFormatString(xPos + 300, yPos, GetColor(255, 255, 255), "←");
		}
	}
}
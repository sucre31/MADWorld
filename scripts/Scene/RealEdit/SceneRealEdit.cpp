#include <DxLib.h>
#include "SceneRealEdit.h"
#include "Sound.h"
#include "Image.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"

SceneRealEdit::SceneRealEdit(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter) {
	sozaiManager.makeSozai("Assets/Sounds/GrandSE/metroBeat.wav", "", 640, 360);
	sozaiManager.addSound(0, "Assets/Sounds/GrandSE/metroBell.wav");

	sequencer.setBPM(120.0f, 2); // 120BPMで2小節分のループ（=4拍×2=8拍）
	sequencer.resetStartTime();
	sequencer.setMetronomeSoundIndex(0);
	sequencer.setAccentMetronomeSoundIndex(1);
	sequencer.setPlay(true);
	sequencer.setMetronome(true);
}

void SceneRealEdit::update() {
	sozaiManager.update(); // ユーザー手動入力も反映

	// 再生
	sequencer.update(sozaiManager);

	// 記録（例：Pad A）
	if (Pad::getIns()->get(ePad::A) == 1) {
		sozaiManager.playSozai(0, 0); // 音を鳴らす
		sequencer.recordTrigger(0, 0, false);
	}

	// ループ再生スタート時
	if (Pad::getIns()->get(ePad::start) == 1) {
		sequencer.resetStartTime();   // 現在時刻を基準にループ開始
		sequencer.setPlay(true);
	}

	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
}

void SceneRealEdit::draw() const {
	sozaiManager.draw();
}
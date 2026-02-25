#include "ScenePizza.h"
#include "Common/Sound.h"
#include "Common/Image.h"
#include "System/Pad.h"
#include "System/Define.h"

ScenePizza::ScenePizza(IOnSceneChangedListener* impl, const Parameter& parameter)
	:AbstractScene(impl, parameter),
	noteManager(140, 4, &sozaiManager)
	{
	sozaiManager.makeSozai("Assets/Sounds/pizza/bass.wav", "Assets/Sprites/movie/pizza/bass0.mp4", Define::WIN_W * (1.0 / 4.0), Define::WIN_H * (1.0 / 4.0));
	sozaiManager.makeSozai("Assets/Sounds/pizza/snea.wav", "Assets/Sprites/movie/pizza/snea.mp4", Define::WIN_W * (2.0 / 4.0), Define::WIN_H * (2.0 / 4.0));
	sozaiManager.makeSozai("Assets/Sounds/pizza/hihat.wav", "Assets/Sprites/movie/pizza/hihat.mp4", Define::WIN_W * (3.0 / 4.0), Define::WIN_H * (3.0 / 4.0));
	for (int i = 0; i < 3; i++) {
		sozaiManager.setSozaiEx(i, (1.0 / 4.0));
		sozaiManager.setReverseFlag(i, true);
	}
	sozaiManager.setSozaiMidiKey(0, eMidi((int)eMidi::C_0), 0, 0);
	sozaiManager.setSozaiMidiKey(1, eMidi((int)eMidi::D_0), 0, 0);
	sozaiManager.setSozaiMidiKey(2, eMidi((int)eMidi::E_0), 0, 0);

	setKey();

	// 効果音読み込み
	SEHandle[0] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/pause.wav");
	SEHandle[1] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/cancel.wav");

	// midiの登録
	MIDI::getIns()->openMidi(0, 0);

	sozaiManager.setDrumFlag(0, true);
	sozaiManager.setDrumFlag(1, true);
	sozaiManager.setDrumFlag(2, true);

}

void ScenePizza::update() {
	sozaiManager.update();
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


void ScenePizza::draw() const{
	sozaiManager.draw();
}

void ScenePizza::setKey() {
	sozaiManager.setSozaiKey(0, ePad::down, 0);
	sozaiManager.setSozaiKey(0, ePad::B, 0);
	sozaiManager.setSozaiKey(1, ePad::A, 0);
	sozaiManager.setSozaiKey(1, ePad::left, 0);
	sozaiManager.setSozaiKey(2, ePad::up, 0);

	sozaiManager.setSozaiMidiKey(0, eMidi((int)eMidi::C_3), 0);
}
#include<Dxlib.h>
#include "ScenePizza.h"
#include "Common/Sound.h"
#include "Common/Image.h"
#include "System/Pad.h"
#include "System/Define.h"

ScenePizza::ScenePizza(IOnSceneChangedListener* impl, const Parameter& parameter)
	:AbstractScene(impl, parameter),
	noteManager(140, 4, &sozaiManager)
	{
	sozaiManager.makeSozai("Assets/Sounds/pizza/bass.wav", "Assets/Sprites/movie/pizza/bass0.mp4", Define::WIN_W * (2.0 / 4.0), Define::WIN_H * (2.0 / 4.0));
	sozaiManager.makeSozai("Assets/Sounds/pizza/snea.wav", "Assets/Sprites/movie/pizza/snea.mp4", Define::WIN_W * (2.0 / 4.0), Define::WIN_H * (2.0 / 4.0));
	sozaiManager.makeSozai("Assets/Sounds/pizza/hihat.wav", "Assets/Sprites/movie/pizza/hihat.mp4", Define::WIN_W * (2.0 / 4.0), Define::WIN_H * (2.0 / 4.0));
	for (int i = 0; i < 3; i++) {
		sozaiManager.setSozaiEx(i, (1.0 / 4.0));
		sozaiManager.setReverseFlag(i, true);
	}
	sozaiManager.setSozaiMidiKey(0, eMidi((int)eMidi::C_0), 0, 0);
	sozaiManager.setSozaiMidiKey(1, eMidi((int)eMidi::D_0), 0, 0);
	sozaiManager.setSozaiMidiKey(2, eMidi((int)eMidi::E_0), 0, 0);

	std::string basePath = "Assets/Sounds/pizza/synth/pizzaSynth";
	std::string moviePath = "Assets/Sprites/movie/pizza/synth.mp4";

	int startMidi = 12;      // C1
	int maxMidi = 127;     // MIDI上限

	int synthIndex1 = -1;
	int soundIndex1 = 0;

	for (int midi = startMidi; midi <= maxMidi; midi++)
	{
		std::string noteName = midiToNoteName(midi);
		std::string filePath = basePath + noteName + ".wav";

		int handle = FileRead_open(filePath.c_str());
		if (handle == -1)
			continue;

		FileRead_close(handle);

		if (synthIndex1 == -1)
		{
			synthIndex1 = sozaiManager.makeSozai(
				filePath.c_str(),
				moviePath.c_str(),
				Define::WIN_W * (1.0 / 4.0),
				Define::WIN_H * (3.0 / 4.0)
			);
			sozaiManager.setSozaiEx(synthIndex1, (1.5 / 4.0));
		}
		else
		{
			sozaiManager.addSound(synthIndex1, filePath.c_str());
		}

		sozaiManager.setSozaiMidiKey(synthIndex1, midi, soundIndex1, 1);
		soundIndex1++;
	}

	int synthIndex2 = -1;
	int soundIndex2 = 0;

	for (int midi = startMidi; midi <= maxMidi; midi++)
	{
		std::string noteName = midiToNoteName(midi);
		std::string filePath = basePath + noteName + ".wav";

		int handle = FileRead_open(filePath.c_str());
		if (handle == -1)
			continue;

		FileRead_close(handle);

		if (synthIndex2 == -1)
		{
			synthIndex2 = sozaiManager.makeSozai(
				filePath.c_str(),
				moviePath.c_str(),
				Define::WIN_W * (3.0 / 4.0),
				Define::WIN_H * (1.0 / 4.0)
			);
			sozaiManager.setSozaiEx(synthIndex2, (1.5 / 4.0));
		}
		else
		{
			sozaiManager.addSound(synthIndex2, filePath.c_str());
		}

		sozaiManager.setSozaiMidiKey(synthIndex2, midi, soundIndex2, 2);
		soundIndex2++;
	}

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

ScenePizza::~ScenePizza() {
	MIDI::getIns()->closeMidi(0);
}

std::string  ScenePizza::midiToNoteName(int midi)
{
	static const char* names[12] = {
		"C","C#","D","D#","E","F",
		"F#","G","G#","A","A#","B"
	};

	int note = midi % 12;
	int octave = (midi / 12) - 1;

	return std::string(names[note]) + std::to_string(octave);
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
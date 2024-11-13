#include <DxLib.h>
#include "SceneLightPlane.h"
#include "Sound.h"
#include "Image.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "MIDI.h"


SceneLightPlane::SceneLightPlane(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	ChangeFont("meiryo");
	SetFontSpace(3);
	SetFontSize(20);
	SetFontThickness(1);

	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample0.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample1.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample2.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample3.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample4.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample5.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample6.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample7.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample8.avi", 640, 360);
	sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample9.avi", 640, 360);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample10.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample11.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample12.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample13.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample14.avi", 0, 0);
	//sozaiManager.makeSozai("", "Assets/sprites/movie/Alice/Samples/AliceSample15.avi", 0, 0);
	sozaiManager.setSozaiMidiKey(0, eMidi::C_3);
	sozaiManager.setSozaiMidiKey(1, eMidi::C_S3);
	sozaiManager.setSozaiMidiKey(2, eMidi::D_3);
	sozaiManager.setSozaiMidiKey(3, eMidi::D_S4);
	sozaiManager.setSozaiMidiKey(4, eMidi::E_4);
	sozaiManager.setSozaiMidiKey(5, eMidi::F_4);
	sozaiManager.setSozaiMidiKey(6, eMidi::F_S4);
	sozaiManager.setSozaiMidiKey(7, eMidi::G_4);
	sozaiManager.setSozaiMidiKey(8, eMidi::G_S4);
	sozaiManager.setSozaiMidiKey(9, eMidi::A_4);

	MIDI::getIns()->openMidi(0 , 0);
}

void SceneLightPlane::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::start) == 1) {
		MIDI::getIns()->closeMidi(0);
		// ƒƒjƒ…[‚É–ß‚é
		Parameter parameter;
		const bool stackClear = true;
		// ‚±‚±‚É’¼Ú‘‚­‚ñ‚¶‚á‚È‚­‚ÄŠÖ”—pˆÓ‚·‚×‚«‚©‚È
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneLightPlane::draw() const {
	sozaiManager.draw();
	MIDI::getIns()->draw();
}
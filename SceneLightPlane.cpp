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

	// ‘fÞ‚Ì“Ç‚Ýž‚Ý‚ÆÝ’è
	sozaiManager.makeSozai("Assets/Sounds/lightPlane/mikotoC_4.wav", "Assets/sprites/images/mikoto.png", 640, 360);
	sozaiManager.setSozaiMidiKey(0, eMidi::C_4, 0);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_S4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::C_S4, 1);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::D_4, 2);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_S4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::D_S4, 3);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoE_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::E_4, 4);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::F_4, 5);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_S4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::F_S4, 6);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::G_4, 7);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_S4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::G_S4, 8);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::A_4, 9);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_S4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::A_S4, 10);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoB_4.wav");
	sozaiManager.setSozaiMidiKey(0, eMidi::B_4, 11);
	sozaiManager.setSozaiEx(0, 0.4);
	sozaiManager.setSozaiPos(0, 640, 360);

	MIDI::getIns()->openMidi(0 , 0);

	// ”wŒi‚ÌÝ’è
	backGround.loadBackImage("Assets/Sprites/images/lightPlaneBack.png");
}

void SceneLightPlane::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::start) == 1) {
		MIDI::getIns()->closeMidi(0);
		clsDx();
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
	backGround.draw();
	sozaiManager.draw();
	MIDI::getIns()->draw();
}
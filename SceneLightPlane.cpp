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

	// ëfçﬁÇÃì«Ç›çûÇ›Ç∆ê›íË
	std::string yasunaFile = "Assets/Sounds/lightPlane/yasuna/yasunaRob";
	sozaiManager.makeSozai((yasunaFile + "0" + std::to_string(1) + ".wav").c_str(), "Assets/sprites/movie/yasuna/yasunaRob.avi", 640, 360);
	for (int i = 1; i < 48; i++) {
		if ((i + 1) < 10) {
			sozaiManager.addSound(0, (yasunaFile + "0" + std::to_string(i + 1) + ".wav").c_str());
		}
		else {
			sozaiManager.addSound(0, (yasunaFile + std::to_string(i + 1) + ".wav").c_str());
		}
	}
	for (int i = 0; i < 48; i++) {
		if (i >= 11) {
			sozaiManager.setSozaiMidiKey(0, eMidi((int)eMidi::C_3 + i), i);
		}
	}
	sozaiManager.setSozaiEx(0, 0.4);
	sozaiManager.setSozaiPos(0, 800, 300);
	sozaiManager.setMultiSound(0, false);

	std::string sonyaFile = "Assets/Sounds/lightPlane/sonya/EdBass/bass";
	sozaiManager.makeSozai((sonyaFile + "01.wav").c_str(), "Assets/sprites/movie/sonya/bass.avi", 640, 360);
	for (int i = 1; i < 48; i++) {
		if ((i + 1) < 10) {
			sozaiManager.addSound(1, (sonyaFile + "0" + std::to_string(i + 1) + ".wav").c_str());
		}
		else {
			sozaiManager.addSound(1, (sonyaFile + std::to_string(i + 1) + ".wav").c_str());
		}
	}
	for (int i = 0; i < 34; i++) {
		if (i >= 10) {
			sozaiManager.setSozaiMidiKey(1, eMidi((int)eMidi::C_0 + i), i);
		}
	}
	sozaiManager.setSozaiEx(1, 0.2);
	sozaiManager.setSozaiPos(1, 280, 580);
	sozaiManager.setMultiSound(1, false);

	sozaiManager.makeSozai("Assets/Sounds/lightPlane/mikotoA_S2.wav", "Assets/sprites/images/mikoto.png", 640, 360);
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoB_2.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoC_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoC_S3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoD_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoD_S3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoE_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoF_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoF_S3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoG_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoG_S3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoA_3.wav");
	sozaiManager.addSound(2, "Assets/Sounds/lightPlane/mikotoA_S3.wav");
	for (int i = 0; i < 13; i++) {
		sozaiManager.setSozaiMidiKey(2, eMidi((int)eMidi::A_S2 + i), i);
	}
	sozaiManager.setSozaiEx(2, 0.1);
	sozaiManager.setSozaiPos(2, 780, 580);
	sozaiManager.setMultiSound(2, true);

	sozaiManager.makeSozai("Assets/Sounds/lightPlane/sonya/kick2.wav", "Assets/sprites/movie/sonya/kick.avi", 640, 360);
	sozaiManager.setSozaiMidiKey(3, eMidi((int)eMidi::C_0), 0);
	sozaiManager.setSozaiEx(3, 0.2);
	sozaiManager.setSozaiPos(3, 280, 380);
	sozaiManager.setMultiSound(3, false);
	sozaiManager.setDrumFlag(3, true);

	sozaiManager.makeSozai("Assets/Sounds/lightPlane/sonya/snea2.wav", "Assets/sprites/movie/sonya/snea.avi", 640, 360);
	sozaiManager.setSozaiMidiKey(4, eMidi((int)eMidi::D_0), 0);
	sozaiManager.setSozaiEx(4, 0.2);
	sozaiManager.setSozaiPos(4, 280, 180);
	sozaiManager.setMultiSound(4, false);
	sozaiManager.setDrumFlag(4, true);

	// midiÇÃìoò^
	MIDI::getIns()->openMidi(0, 0);
	MIDI::getIns()->openMidi(1 ,1);

	// îwåiÇÃê›íË
	backGround.loadBackImage("Assets/Sprites/images/lightPlaneBack.png");
	backGround.setExRate(2.0 / 3.0);
}

void SceneLightPlane::update() {
	sozaiManager.update();
	if (Pad::getIns()->get(ePad::start) == 1) {
		MIDI::getIns()->closeMidi(0);
		clsDx();
		// ÉÅÉjÉÖÅ[Ç…ñﬂÇÈ
		Parameter parameter;
		const bool stackClear = true;
		// Ç±Ç±Ç…íºê⁄èëÇ≠ÇÒÇ∂Ç·Ç»Ç≠Çƒä÷êîópà”Ç∑Ç◊Ç´Ç©Ç»
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
	}
	if (Pad::getIns()->get(ePad::L) == 1) {
		clsDx();
	}
}

void SceneLightPlane::draw() const {
	backGround.draw();
	sozaiManager.draw();
	MIDI::getIns()->draw();
}
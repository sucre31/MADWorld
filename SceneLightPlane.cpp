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
	sozaiManager.makeSozai("Assets/Sounds/lightPlane/mikotoF_S2.wav", "Assets/sprites/images/mikoto.png", 640, 360);
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_2.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_S2.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_2.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_S2.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoB_2.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_S3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_S3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoE_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_S3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_S3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_S3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoB_3.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_S4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_S4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoE_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_S4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_S4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_S4.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoB_4.wav");


	for (int i = 0; i < 31; i++) {
		sozaiManager.setSozaiMidiKey(0, eMidi((int)eMidi::F_S3 + i), i);
	}

	sozaiManager.makeSozai("Assets/Sounds/lightPlane/mikotoA_1.wav", "Assets/sprites/images/mikoto.png", 640, 360);
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoA_S1.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoB_1.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoC_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoC_S2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoD_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoD_S2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoE_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoF_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoF_S2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoG_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoG_S2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoA_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoA_S2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoB_2.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoC_3.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoC_S3.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoD_3.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoD_S3.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoE_3.wav");
	sozaiManager.addSound(1, "Assets/Sounds/lightPlane/mikotoF_3.wav");

	for (int i = 0; i < 21; i++) {
		sozaiManager.setSozaiMidiKey(1, eMidi((int)eMidi::A_1 + i), i);
	}

	sozaiManager.setSozaiEx(0, 0.4);
	sozaiManager.setSozaiPos(0, 800, 300);
	sozaiManager.setMultiSound(0, true);

	sozaiManager.setSozaiEx(1, 0.2);
	sozaiManager.setSozaiPos(1, 280, 580);
	sozaiManager.setMultiSound(1, true);


	MIDI::getIns()->openMidi(0 , 0);

	// îwåiÇÃê›íË
	backGround.loadBackImage("Assets/Sprites/images/lightPlaneBack.png");
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
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneLightPlane::draw() const {
	backGround.draw();
	sozaiManager.draw();
	MIDI::getIns()->draw();
}
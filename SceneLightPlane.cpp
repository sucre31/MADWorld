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
	sozaiManager.makeSozai("Assets/Sounds/lightPlane/mikotoC_3.wav", "Assets/sprites/images/mikoto.png", 640, 360);
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
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoC_S5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoD_S5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoE_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoF_S5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoG_S5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoA_S5.wav");
	sozaiManager.addSound(0, "Assets/Sounds/lightPlane/mikotoB_5.wav");


	for (int i = 0; i < 36; i++) {
		sozaiManager.setSozaiMidiKey(0, eMidi(48 + i), i);
	}

	sozaiManager.setSozaiEx(0, 0.4);
	sozaiManager.setSozaiPos(0, 640, 360);

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
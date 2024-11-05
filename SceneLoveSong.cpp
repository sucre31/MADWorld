#include <DxLib.h>
#include "Sound.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "SceneLoveSong.h"


SceneLoveSong::SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	currentSoundIndex = 0;
	Sound::getIns()->loadLoveSongSamples();
}

void SceneLoveSong::update()
{
	if (Pad::getIns()->get(ePad::down) == 1) {
		playSampleSound(0);
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		playSampleSound(1);
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		playSampleSound(2);
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		playSampleSound(3);
	}
	if (Pad::getIns()->get(ePad::Y) == 1) {
		playSampleSound(4);
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		playSampleSound(5);
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		playSampleSound(6);
	}
	if (Pad::getIns()->get(ePad::X) == 1) {
		playSampleSound(7);
	}
}

void SceneLoveSong::playSampleSound(int num) {
	StopSoundMem(Sound::getIns()->getLoveSongSamples()[currentSoundIndex]);
	PlaySoundMem(Sound::getIns()->getLoveSongSamples()[num], DX_PLAYTYPE_BACK);
	currentSoundIndex = num;
}

void SceneLoveSong::draw() const
{
	DrawString(500, 300, "‚Ó‚Á‚©‚Â‚Ì‚¶‚ã‚à‚ñ", GetColor(255, 255, 255));
}
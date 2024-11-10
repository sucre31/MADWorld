#include <Dxlib.h>
#include "Image.h"
#include "Sozai.h"
#include "Sound.h"
#include "Pad.h"

Sozai::Sozai() {
	x = 0;
	y = 0;
	enableTurn = false;
	turnFlag = false;
}

bool Sozai::update() {
	if (Pad::getIns()->get(ePad(triggerButton)) == 1) {
		playSample();
	}
	return true;
}

void Sozai::draw() const {
	DrawRotaGraph(x, y, 1.0, 0, myGrapghHandle, FALSE, enableTurn && turnFlag);
}

void Sozai::playSample() {
	turnFlag = !turnFlag;	// ”½“]

	// ‰¹ºˆ—
	StopSoundMem(mySoundHandle);
	PlaySoundMem(mySoundHandle, DX_PLAYTYPE_BACK);
	// ‰f‘œˆ—(‰f‘œ‚È‚ç‚Á‚Ä‚¢‚¤ðŒ‚¢‚é‚©‚àA‚à‚µ‚­‚Í‰f‘œ‚à‰æ‘œ‚Ì˜A”Ô‚Æ‚µ‚Äˆ—‚Å‚«‚é‚æ‚¤‚É©–³‘Ê‚ª‚È‚¢)
	SeekMovieToGraph(myGrapghHandle, 0);
	PlayMovieToGraph(myGrapghHandle);
}

void Sozai::setSampleMovie(const char* fileName) {
	myGrapghHandle = Image::getIns()->loadSamples(fileName);
}

void Sozai::setSampleSound(const char* fileName) {
	mySoundHandle = Sound::getIns()->loadSamples(fileName);
}
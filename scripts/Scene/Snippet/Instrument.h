#pragma once
#include <memory>
#include "BeatManager.h"
#include "SnippetSound.h"

class Instrument
{
public:
	Instrument(std::shared_ptr<SnippetSound> sound);
	~Instrument() = default;
	void playMainInstrument(int NumberOfTone);
	void playSubInstrument(int NumberOfTone);
	void setMyInstrumentNumber(int Number) { myInstrumentNumber = Number; }
	bool playWithStep(int stepNumber, int checkMode);
	//void setBeatManager(BeatManager* beatManagerInstance) { beatManager = beatManagerInstance; }
private:
	int myInstrumentNumber;
	//BeatManager* beatManager;
	std::shared_ptr<SnippetSound> snippetSound;
};


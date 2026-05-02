#include "EndingAction.h"
#include "Scene/Snippet/BeatManager.h"

void EndingAction::execute() {
	beatManager->startMusic(musicNo);
}
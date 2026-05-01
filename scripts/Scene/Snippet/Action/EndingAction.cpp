#include "EndingAction.h"
#include "Scene/Snippet/BeatManager.h"

void EndingAction::execute() {
	printfDx("aa");
	beatManager->startMusic(musicNo);
}
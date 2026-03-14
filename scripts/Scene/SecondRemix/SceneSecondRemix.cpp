#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	objectionManager.setSozaiManager(&sozaiManager);
	objectionManager.initSozai();
}

void SceneSecondRemix::update() {
	objectionManager.update();
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
}
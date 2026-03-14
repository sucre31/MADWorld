#include "SceneSecondRemix.h"

SceneSecondRemix::SceneSecondRemix(IOnSceneChangedListener* impl, const Parameter& parameter)
	: AbstractScene(impl, parameter),
	noteManager(132, 4, &sozaiManager) 
{
	int back = sozaiManager.makeSozai("", "Assets/Sprites/images/secondRemix/back.png", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager.setSozaiLayer(back, 0);

	objectionManager.setSozaiManager(&sozaiManager);
	objectionManager.initSozai();
	objectionManager.setActive(true);

	donesiaManager.setSozaiManager(&sozaiManager);
	donesiaManager.initSozai();
	donesiaManager.setActive(false);
}

void SceneSecondRemix::update() {
	if (Pad::getIns()->get(ePad::change) == 1) {
		objectionManager.setActive(true);
		donesiaManager.setActive(false);
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		objectionManager.setActive(false);
		donesiaManager.setActive(true);
	}
	objectionManager.update();
	donesiaManager.update();
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
}
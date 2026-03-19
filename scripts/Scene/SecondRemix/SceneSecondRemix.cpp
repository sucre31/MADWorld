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

	dontacoManager.setSozaiManager(&sozaiManager);
	dontacoManager.initSozai();
	dontacoManager.setActive(false);

	activeManagerIndex = 0;
}

void SceneSecondRemix::update() {
	int prevMangerIndex = activeManagerIndex;
	if (Pad::getIns()->get(ePad::change) == 1) {
		activeManagerIndex--;
		if (activeManagerIndex < 0) {
			activeManagerIndex = 0;
		}
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		activeManagerIndex++;
		if (activeManagerIndex >= sozaiManagerCount) {
			activeManagerIndex = sozaiManagerCount - 1;
		}
	}
	if (prevMangerIndex != activeManagerIndex) {
		switch (activeManagerIndex) {
		case 0:
			objectionManager.setActive(true);
			donesiaManager.setActive(false);
			dontacoManager.setActive(false);
			break;
		case 1:
			objectionManager.setActive(false);
			donesiaManager.setActive(true);
			dontacoManager.setActive(false);
			break;
		case 2:
			objectionManager.setActive(false);
			donesiaManager.setActive(false);
			dontacoManager.setActive(true);
			break;
		}
	}

	objectionManager.update();
	donesiaManager.update();
	sozaiManager.update();
}


void SceneSecondRemix::draw() const{
	sozaiManager.draw();
}
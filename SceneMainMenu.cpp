#include <DxLib.h>
#include "SceneMainMenu.h"
#include "Image.h"
#include "Pad.h"

SceneMainMenu::SceneMainMenu(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	cursorIns.loadCurorImage("Assets/Sprites/images/MainMenu/cursor.png");
	backGround.loadBackImage("Assets/Sprites/images/MainMenu/UISample.png");
}

void SceneMainMenu::update()
{
	double speedRate = 2.0;
	if (Pad::getIns()->get(ePad::Y) >= 1) {
		speedRate = 3.0;
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		Parameter parameter;
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
    if (Pad::getIns()->get(ePad::up) >= 1) {
		cursorIns.plusPos(0, -0.1 * speedRate);
    }
	if (Pad::getIns()->get(ePad::down) >= 1) {
		cursorIns.plusPos(0, 0.1 * speedRate);
	}
	if (Pad::getIns()->get(ePad::right) >= 1) {
		cursorIns.plusPos(0.1 * speedRate, 0);
	}
	if (Pad::getIns()->get(ePad::left) >= 1) {
		cursorIns.plusPos(-0.1 * speedRate, 0);
	}
}

void SceneMainMenu::draw() const
{
	backGround.draw();
	cursorIns.draw();
}
#pragma once
#include "AbstractScene.h"
#include "Sound.h"
#include "Define.h"
#include "Image.h"
#include "Keyboard.h"
#include "Pad.h"
#include "GameObject.h"

class PauseMenu : GameObject
{
public:
	PauseMenu();
	~PauseMenu() = default;
	bool update() override;
	void draw() const override;
	void setActive();
	bool getActive() { return activeMenu; }
	int getSelectCmd() { return selectCmd; }
private:
	int graphHandle;
	int seHandle;
	bool activeMenu;
	int selectCmd;
};


#pragma once
#include "System/AbstractScene.h"
#include "Common/Sound.h"
#include "System/Define.h"
#include "Common/Image.h"
#include "System/Keyboard.h"
#include "System/Pad.h"
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


#pragma once
#include <memory>
#include <DxLib.h>
#include "System/AbstractScene.h"
#include "cursor.h"
#include "Common/GameObject/BackGround.h"
#include "gameIcon.h"
class SceneMainMenu : public AbstractScene
{
public:
    SceneMainMenu(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneMainMenu() = default;
    void update() override;
    void draw() const override;
    int getIconScene(int );
private:
	enum class MenuState {
		MainMenu,
		ExtraMenu
	};
    MenuState currentState = MenuState::MainMenu;
    std::vector<std::unique_ptr<gameIcon>> dynamicIcons;
    std::vector<std::string> jsonPaths;
    int dynamicStageCount = 0;

	void LoadDynamicStages();

    static const int iconNum = 11;
    int validIconNum;
    int selectIconNo;               // -1: 選択無し
    cursor cursorIns;
    BackGround backGround;
    int musicHandle;
    gameIcon icon[iconNum];
};


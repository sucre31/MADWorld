#pragma once
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
    static const int iconNum = 8;
    int validIconNum;
    int selectIconNo;               // -1: ‘I‘ð–³‚µ
    cursor cursorIns;
    BackGround backGround;
    int musicHandle;
    gameIcon icon[iconNum];
};


#pragma once
#include "AbstractScene.h"
#include "cursor.h"
#include "BackGround.h"
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
    static const int iconNum = 4;
    int validIconNum;
    int selectIconNo;               // -1: �I�𖳂�
    cursor cursorIns;
    BackGround backGround;
    int musicHandle;
    gameIcon icon[iconNum];
};


#pragma once
#include "AbstractScene.h"
#include "cursor.h"
#include "BackGround.h"
class SceneMainMenu : public AbstractScene
{
public:
    SceneMainMenu(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneMainMenu() = default;
    void update() override;
    void draw() const override;
private:
    cursor cursorIns;
    BackGround backGround;
};


#pragma once
#include "AbstractScene.h"

class TitleScene : public AbstractScene
{
public:
    TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~TitleScene() = default;
    void update() override;
    void draw() const override;
private:
    int SEHandle[3];
    int selectNum;
    int cursorY;
    int musicHandle;
    int titleGraphHandle;
    int buttonHandle[8];
    int keyUpTime;
    int keyDownTime;
};

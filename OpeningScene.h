#pragma once
#include "AbstractScene.h"

class OpeningScene : public AbstractScene
{
public:
    OpeningScene(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~OpeningScene() = default;
    void update() override;
    void draw() const override;
private:
    int musicHandle;
    int SEHandle;
    bool isStart;
    int titleGraphHandle;
};


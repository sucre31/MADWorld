#pragma once
#include "AbstractScene.h"
class SceneLoveSong : public AbstractScene
{
public:
    SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneLoveSong() = default;
    void update() override;
    void draw() const override;
private:
    int currentSoundIndex;
    void playSampleSound(int);
};


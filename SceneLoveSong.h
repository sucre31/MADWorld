#pragma once
#include "AbstractScene.h"
class SceneLoveSong : public AbstractScene
{
public:
    SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneLoveSong() = default;
    void update() override;
    void draw() const override;
    void addReviveChar(std::string);
private:
    const int strSize = 74;
    int currentSoundIndex;
    void playSampleSound(int);
    bool isMusicPlay;
    std::string stringRevive;
    int strIndex;
};


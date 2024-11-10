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
    void resetString();
private:
    const int strSize = 74;
    int currentSoundIndex;
    int currentMovieIndex;
    bool movieTurnFlag;
    int musicIndex;
    void playSampleSound(int);
    bool isMusicPlay;
    std::string stringRevive;
    int strIndex;
};


#pragma once
#include "AbstractScene.h"
class SceneOption : public AbstractScene
{
    //MIDI����̐ݒ肩��
public:
    SceneOption(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneOption() = default;
    void update() override;
    void draw() const override;
private:
    int midiNum;
    TCHAR* midiInfo;
};


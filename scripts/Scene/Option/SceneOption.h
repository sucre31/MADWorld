#pragma once
#include "System/AbstractScene.h"
class SceneOption : public AbstractScene
{
    //MIDIü‚è‚Ìİ’è‚©‚È
public:
    SceneOption(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneOption() = default;
    void update() override;
    void draw() const override;
private:
    int midiNum;
    TCHAR* midiInfo;
};


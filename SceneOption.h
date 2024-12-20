#pragma once
#include "AbstractScene.h"
class SceneOption : public AbstractScene
{
    //MIDI周りの設定かな
public:
    SceneOption(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneOption() = default;
    void update() override;
    void draw() const override;
private:
    int midiNum;
    TCHAR* midiInfo;
};


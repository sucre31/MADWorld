#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"

class SceneLightPlane : public AbstractScene
{
public:
    SceneLightPlane(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneLightPlane() = default; // デストラクタ多分大事 後で調整
    void update() override;
    void draw() const override;
private:
    // シーンはインスタンスを管理するだけ
    SozaiManager sozaiManager;
    BackGround backGround;
};


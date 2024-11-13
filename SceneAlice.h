#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class SceneAlice : public AbstractScene
{
public:
    SceneAlice(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneAlice() = default; // デストラクタ多分大事 後で調整
    void update() override;
    void draw() const override;
private:
    // シーンはインスタンスを管理するだけ
    SozaiManager sozaiManager;
    int aliceDrumHandle; // クラスかする
    bool isMusicPlay;
};


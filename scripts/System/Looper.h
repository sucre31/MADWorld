#pragma once

#include <stack>
#include <memory>
#include "System/AbstractScene.h"
#include "System/IOnSceneChangedListener.h"
#include "System/FpsControl.h"
#include "System/Define.h"

class Looper final : public IOnSceneChangedListener
{
public:
    Looper();
    ~Looper() = default;
    bool loop() const;
    void onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear) override;

private:
    int screenRate;
    bool useDebug;
    std::stack<std::shared_ptr<AbstractScene>> _sceneStack; //シーンのスタック
    //std::shared_ptr<FpsControl> _fps;
    FpsControl* _fps;
};
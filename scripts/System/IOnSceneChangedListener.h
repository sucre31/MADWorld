#pragma once
#include "System/eScene.h"
#include "System/AbstractScene.h"
#include "System/Parameter.h"

class IOnSceneChangedListener
{
public:
    IOnSceneChangedListener() = default;
    virtual ~IOnSceneChangedListener() = default;
    virtual void onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear) = 0;
};

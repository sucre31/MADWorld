#pragma once
#include "System/IOnSceneChangedListener.h"
#include "System/Parameter.h"

class IOnSceneChangedListener;

class AbstractScene
{
protected:
    IOnSceneChangedListener* _implSceneChanged;
public:
    AbstractScene(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~AbstractScene() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
};

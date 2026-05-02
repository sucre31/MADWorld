#pragma once

#include "System/AbstractScene.h"
#include <vector>
#include <string>

class TitleForLive : public AbstractScene
{
public:
    TitleForLive(IOnSceneChangedListener* impl, const Parameter& parameter);

    void update() override;
    void draw() const override;

private:
    int selectNum;
    int bgHandle;

    struct MenuItem {
        std::string name;
        eScene nextScene;
    };

    std::vector<MenuItem> menu;
};
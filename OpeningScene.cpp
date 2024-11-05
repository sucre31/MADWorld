#include <DxLib.h>
#include "Pad.h"
#include "OpeningScene.h"

OpeningScene::OpeningScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("しねきゃぷしょん");
    SetFontSpace(1);
    SetFontSize(36);
    SetFontThickness(1);
}

void OpeningScene::update() {
    // とりあえずスタートキー
    if (Pad::getIns()->get(ePad::start) == 1) {
        Parameter parameter;
        const bool stackClear = true;
        _implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
        return;
    }
}

void OpeningScene::draw() const{
    DrawString(500, 40, "MAD Heaven", GetColor(255, 255, 255));

    DrawString(500, 540, "Press Any Key", GetColor(255, 255, 255));
}
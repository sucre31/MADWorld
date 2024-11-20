#include <DxLib.h>
#include "TitleScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "Sound.h"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("ÇµÇÀÇ´Ç·Ç’ÇµÇÂÇÒ");
    SetFontSpace(1);
    SetFontSize(36);
    SetFontThickness(1);
    selectNum = 0;
}

void TitleScene::update()
{
    if (Pad::getIns()->get(ePad::up) == 1) {
        selectNum = (selectNum + 3) % 4;
        return;
    }
    if (Pad::getIns()->get(ePad::down) == 1) {
        selectNum = ++selectNum % 4;
        return;
    }
    if (Pad::getIns()->get(ePad::A) == 1) {
        Parameter parameter;
        if (selectNum == 0) {
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
        }
        else if (selectNum == 1) {
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::Alice, parameter, stackClear);
        }
        else if (selectNum == 2) {
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::Option, parameter, stackClear);
        }
        else {
            //quit
            DxLib_End();
        }
        return;
    }
    if (selectNum == 0) {
        cursorY = 300;
    }
    else if (selectNum == 1) {
        cursorY = 400;
    }
    else if (selectNum == 2) {
        cursorY = 500;
    }
    else {
        cursorY = 600;
    }
}

void TitleScene::draw() const
{

    DrawString(500, 40, "MAD Heaven", GetColor(255, 255, 255));
    DrawString(500, 300, "Main Game", GetColor(255, 255, 255));
    DrawString(500, 400, "Extra", GetColor(255, 255, 255));
    DrawString(500, 500, "Option", GetColor(255, 255, 255));
    DrawString(500, 600, "quit", GetColor(255, 255, 255));
    DrawString(400, cursorY, "ÅE", GetColor(255, 255, 255));
}

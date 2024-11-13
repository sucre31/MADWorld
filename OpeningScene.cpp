#include <DxLib.h>
#include "Pad.h"
#include "OpeningScene.h"
#include "Sound.h"


OpeningScene::OpeningScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("‚µ‚Ë‚«‚á‚Õ‚µ‚å‚ñ");
    SetFontSpace(1);
    SetFontSize(36);
    SetFontThickness(1);
    PlaySoundMem(Sound::getIns()->getTitleHandle(), DX_PLAYTYPE_LOOP, TRUE);
    isStart = FALSE;
}

void OpeningScene::update() {
    if (Pad::getIns()->get(ePad::A) == 1) {
        isStart = TRUE;
    }
    if (isStart) {
        StopSoundMem(Sound::getIns()->getTitleHandle());
        Parameter parameter;
        const bool stackClear = true;
        _implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
        return;
    }
}

void OpeningScene::draw() const{
    DrawString(500, 40, "MAD Heaven", GetColor(255, 255, 255));

    DrawString(500, 540, "Press A", GetColor(255, 255, 255));
}
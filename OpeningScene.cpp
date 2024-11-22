#include <DxLib.h>
#include "Pad.h"
#include "OpeningScene.h"
#include "Sound.h"
#include "Image.h"


OpeningScene::OpeningScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("AR PƒSƒVƒbƒN‘ÌS");
    SetFontSpace(1);
    SetFontSize(50);
    SetFontThickness(1);
    ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
    SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
    musicHandle = Sound::getIns()->loadSamples("Assets/Sounds/title/title.wav");
    SEHandle = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/start.wav");
    SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
    PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, TRUE);
    isStart = FALSE;
    titleGraphHandle = Image::getIns()->loadSamples("Assets/Sprites/images/title/titleScreen.png");
}

void OpeningScene::update() {
    if (Pad::getIns()->get(ePad::A) == 1) {
        PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK, TRUE);
        isStart = TRUE;
    }
    if (isStart) {
        StopSoundMem(musicHandle);
        Parameter parameter;
        const bool stackClear = true;
        _implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
        return;
    }
}

void OpeningScene::draw() const{
    DrawGraph(0, 0, titleGraphHandle, FALSE);

    DrawString(500, 540, "Press A", GetColor(0, 0, 0));
}
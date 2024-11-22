#include <DxLib.h>
#include "TitleScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "Image.h"
#include "Sound.h"

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("AR Pゴシック体S");
    SetFontSpace(1);
    SetFontSize(50);
    SetFontThickness(1);
    selectNum = 0;
    SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
    musicHandle = Sound::getIns()->loadSamples("Assets/Sounds/Menu/Menu1.wav");
    SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
    PlaySoundMem(musicHandle, DX_PLAYTYPE_LOOP, TRUE);
    titleGraphHandle = Image::getIns()->loadSamples("Assets/Sprites/images/title/titleScreen.png");
    buttonHandle[0] = Image::getIns()->loadSamples("Assets/Sprites/images/title/mainButton1.png");
    buttonHandle[1] = Image::getIns()->loadSamples("Assets/Sprites/images/title/mainButton2.png");
    buttonHandle[2] = Image::getIns()->loadSamples("Assets/Sprites/images/title/ExtraButton1.png");
    buttonHandle[3] = Image::getIns()->loadSamples("Assets/Sprites/images/title/ExtraButton2.png");
    buttonHandle[4] = Image::getIns()->loadSamples("Assets/Sprites/images/title/optionButton1.png");
    buttonHandle[5] = Image::getIns()->loadSamples("Assets/Sprites/images/title/optionButton2.png");
    buttonHandle[6] = Image::getIns()->loadSamples("Assets/Sprites/images/title/QuitButton1.png");
    buttonHandle[7] = Image::getIns()->loadSamples("Assets/Sprites/images/title/QuitButton2.png");

    SEHandle[0] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/select.wav");
    SEHandle[1] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/define.wav");
    SEHandle[2] = Sound::getIns()->loadSamples("Assets/Sounds/GrandSE/cancel.wav");
}

void TitleScene::update()
{
    if (Pad::getIns()->get(ePad::up) == 1) {
        PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK, TRUE);
        selectNum = (selectNum + 3) % 4;
        return;
    }
    if (Pad::getIns()->get(ePad::down) == 1) {
        PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK, TRUE);
        selectNum = ++selectNum % 4;
        return;
    }
    if (Pad::getIns()->get(ePad::A) == 1) {
        Parameter parameter;
        if (selectNum == 0) {
            PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK, TRUE);
            StopSoundMem(musicHandle);
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::MainMenu, parameter, stackClear);
        }
        else if (selectNum == 1) {
            PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK, TRUE);
            StopSoundMem(musicHandle);
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::Alice, parameter, stackClear);
        }
        else if (selectNum == 2) {
            PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK, TRUE);
            StopSoundMem(musicHandle);
            const bool stackClear = true;
            _implSceneChanged->onSceneChanged(eScene::Option, parameter, stackClear);
        }
        else {
            //quit
            DxLib_End();
        }
        return;
    }
    if (Pad::getIns()->get(ePad::B) == 1) {
        PlaySoundMem(SEHandle[2], DX_PLAYTYPE_BACK, TRUE);
        Parameter parameter;
        StopSoundMem(musicHandle);
        const bool stackClear = true;
        _implSceneChanged->onSceneChanged(eScene::Opening, parameter, stackClear);
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
    DrawGraph(0, 0, titleGraphHandle, FALSE);
    for (int i = 0; i < 4; i++) {
        if (selectNum == i) {
            DrawGraph(650, 260 + 120 * i, buttonHandle[i * 2 + 1], TRUE);
        }
        else {
            DrawGraph(650, 260 + 120 * i, buttonHandle[i * 2], TRUE);
        }
    }
    switch (selectNum) {
    case 0:
        DrawString(50, 400, "基本となるゲームモード!", GetColor(0, 0, 0));
        break;
    case 1:
        DrawString(50, 400, "おまけコンテンツです", GetColor(0, 0, 0));
        break;
    case 2:
        DrawString(50, 400, "MIDIデバイスなど\n各種設定を行います", GetColor(0, 0, 0));
        break;
    case 3:
        DrawString(50, 400, "ゲームを終了します", GetColor(0, 0, 0));
        break;
    }
}

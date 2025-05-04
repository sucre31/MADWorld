#include<Dxlib.h>
#include "SceneOption.h"
#include "System/Keyboard.h"
#include "System/Pad.h"
#include "Common/Sound.h"
#include "System/MIDI.h"

SceneOption::SceneOption(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
    ChangeFont("meiryo");
    SetFontSpace(3);
    SetFontSize(20);
    SetFontThickness(1);
    midiNum = 0;
    MIDI::getIns()->openMidi(midiNum, midiNum);
    midiInfo = MIDI::getIns()->getMidiInfo();
}

void SceneOption::update()
{
    if (Pad::getIns()->get(ePad::up) == 1) {
        MIDI::getIns()->closeMidi(midiNum);
        midiNum++;
        MIDI::getIns()->openMidi(midiNum, midiNum);
        midiInfo = MIDI::getIns()->getMidiInfo();
        return;
    }
    if (Pad::getIns()->get(ePad::down) == 1) {
        if (midiNum > 0) {
            MIDI::getIns()->closeMidi(midiNum);
            midiNum--;
            MIDI::getIns()->openMidi(midiNum, midiNum);
            midiInfo = MIDI::getIns()->getMidiInfo();
            return;
        }
    }
    if (Pad::getIns()->get(ePad::B) == 1) {
        MIDI::getIns()->closeMidi(midiNum);
        clsDx();
        Parameter parameter;
        const bool stackClear = false;
        _implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
    }
}


void SceneOption::draw() const
{
    unsigned int Color;
    Color = GetColor(255, 255, 255);
    if (midiInfo != NULL) {
        DrawFormatString(0, 700, Color, "%s", midiInfo);
    }
}

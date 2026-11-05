#include <DxLib.h>
#include "NoteUIManager.h"
#include "Common/Image.h"

NoteUIManager::NoteUIManager(NoteManager& nm, SozaiManager& sm)
    : noteManager(nm), sozaiManager(sm)
{
    // NoteManagerから移行した画像読み込み
    std::string notePath = "Assets/Sprites/images/Common/notesGem";
    noteImages[0] = Image::getIns()->loadSamples((notePath + "/down.png").c_str());
    noteImages[1] = Image::getIns()->loadSamples((notePath + "/left.png").c_str());
    noteImages[2] = Image::getIns()->loadSamples((notePath + "/up.png").c_str());
    noteImages[3] = Image::getIns()->loadSamples((notePath + "/right.png").c_str());
    noteImages[4] = Image::getIns()->loadSamples((notePath + "/buttonY.png").c_str());
    noteImages[5] = Image::getIns()->loadSamples((notePath + "/buttonB.png").c_str());
    noteImages[6] = Image::getIns()->loadSamples((notePath + "/buttonA.png").c_str());
    noteImages[7] = Image::getIns()->loadSamples((notePath + "/buttonX.png").c_str());
}

bool NoteUIManager::update() {
    return true;
}

void NoteUIManager::draw() const {
    int currentMs = noteManager.getCurrentTimeMs();

    bool drawnTargetIds[100] = { false };

    for (const auto& note : noteManager.getNotes()) {
        int id = note.inputId;
        // まだ判定枠を描画していないアセットIDなら描画
        if (id >= 0 && id < 100 && !drawnTargetIds[id]) {
            double targetX = sozaiManager.getSozaiPosX(id);
            double targetY = sozaiManager.getSozaiPosY(id);

            // ジャストタイミング (progress == 0) の時の到達座標
            int hitX = static_cast<int>(targetX);
            int hitY = static_cast<int>(targetY - 200);

            // 半透明の白い円枠を描画(仮)
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
            DrawCircle(hitX, hitY, 35, GetColor(255, 255, 255), FALSE, 3);

            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            drawnTargetIds[id] = true;
        }
    }

    for (const auto& note : noteManager.getNotes()) {
        if (note.hit || note.missed) continue;

        int noteTime = note.getTimeMs(noteManager.getBpm(), noteManager.getBeatsPerBar());
        int timeUntilHit = noteTime - currentMs;


        // まだ出現時間になっていない、または既に通り過ぎたノーツは描画しない
        if (timeUntilHit > appearDurationMs || timeUntilHit < -100) continue;

        // 素材の座標を取得
        double targetX = sozaiManager.getSozaiPosX(note.inputId);
        double targetY = sozaiManager.getSozaiPosY(note.inputId);

        // 進行度
        float progress = static_cast<float>(timeUntilHit) / appearDurationMs;
        if (progress < 0.0f) progress = 0.0f;

        // 頭上に上から降ってくる(仮)
         int drawX = targetX;
         int drawY = (targetY - 200) - (progress * 200);
         float scale = 0.75;
         int alpha = 155;


        ePad pad = sozaiManager.getMappedPad(note.inputId, note.soundIndex);

        int imgIdx = 0; // デフォルト画像
        switch (pad) {
        case ePad::down:  imgIdx = 0; break;
        case ePad::left:  imgIdx = 1; break;
        case ePad::up:    imgIdx = 2; break;
        case ePad::right: imgIdx = 3; break;
        case ePad::Y:     imgIdx = 4; break;
        case ePad::B:     imgIdx = 5; break;
        case ePad::A:     imgIdx = 6; break;
        case ePad::X:     imgIdx = 7; break;
        default:          imgIdx = 0; break; // LやRなど、画像がないボタンのフォールバック
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

        DrawRotaGraph(static_cast<int>(drawX), static_cast<int>(drawY), scale, 0.0, noteImages[imgIdx], TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}
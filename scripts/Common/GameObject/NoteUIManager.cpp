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
    int currentMs = noteManager.getCurrentTimeMs(); // GetNowCount() - playStartTimeMs;

    for (const auto& note : noteManager.getNotes()) {
        if (note.hit || note.missed) continue;

        int noteTime = note.getTimeMs(noteManager.getBpm(), noteManager.getBeatsPerBar());
        int timeUntilHit = noteTime - currentMs;

        // 判定時間を過ぎて一定時間経ったらMiss扱いにするなどの処理もここで可能
        // (本来はNoteManagerのupdateでやるのが綺麗ですが)

        // まだ出現時間になっていない、または既に通り過ぎたノーツは描画しない
        if (timeUntilHit > appearDurationMs || timeUntilHit < -100) continue;

        // 素材の座標を取得
        double targetX = sozaiManager.getSozaiPosX(note.inputId);
        double targetY = sozaiManager.getSozaiPosY(note.inputId);

        // 進行度 (1.0: 出現時 -> 0.0: 判定ドンピシャ)
        float progress = static_cast<float>(timeUntilHit) / appearDurationMs;
        if (progress < 0.0f) progress = 0.0f;

        // --- 描画の演出例 ---
        // 例1：頭上に上から降ってくる
         int drawX = targetX;
         int drawY = (targetY - 200) - (progress * 200); // 300px上から落ちてくる
         float scale = 0.75;
         int alpha = 155;

        // 例2：その場で徐々に拡大して実体化する（osu!のアプローチサークルのようなイメージ）
        //int drawX = targetX;
        //int drawY = targetY;
        //float scale = 0.5f + (progress * 1.5f); // 大きく出現して適切なサイズに縮む
        //int alpha = 255 - (progress * 255);     // 透明からフェードイン

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

        // imgIdx を使って正しいボタン画像を描画する
        DrawRotaGraph(static_cast<int>(drawX), static_cast<int>(drawY), scale, 0.0, noteImages[imgIdx], TRUE);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}
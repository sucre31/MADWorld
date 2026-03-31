#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include "NoteManager.h"
#include <DxLib.h>
#include "Common/Time.h"
#include "System/Define.h"
#include "Common/Image.h"

NoteManager::NoteManager(int bpm, int beatsPerBar, SozaiManager* sozai)
    : bpm(bpm), beatsPerBar(beatsPerBar) , playbackPool(3){
    timeBeginPeriod(1);
    barDurationMs = (60000 * beatsPerBar) / bpm;
    barWidthPx = static_cast<int>(Define::WIN_W * 0.4);
    startX = static_cast<int>(Define::WIN_W * 0.3);

    sozaiManager = sozai;
    BGMHandle = -1;

    // オートはデフォルトオフ
    useAutoPlay = true;

    // ノート画像読み込み
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

bool NoteManager::loadFromFile(const std::string& path) {
    // 適当だから実装しなおす

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open note file: " << path << std::endl;
        return false;
    }

    notes.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // コメント行

        std::istringstream ss(line);
        Note note;

        // 仮フォーマット: bar,beat,subdivision,subdivisionCount,inputId
        char delim;
        ss >> note.bar >> delim
            >> note.beat >> delim
            >> note.subdivision >> delim
            >> note.subdivisionCountPerBeat >> delim
            >> note.inputId;

        if (ss.fail()) {
            std::cerr << "Invalid line in note file: " << line << std::endl;
            continue;
        }

        notes.push_back(note);
    }

    std::cout << "Loaded " << notes.size() << " notes from " << path << std::endl;
    return true;
}

bool NoteManager::update() {
    setCurrentTimeMs((int)GetSoundCurrentTime(BGMHandle));
    updateAutoPlay();
    return true;
}

void NoteManager::updateAutoPlay() {
    if (useAutoPlay) {
        int currentMs = (int)GetSoundCurrentTime(BGMHandle);

        for (auto& note : notes) {
            if (note.hit) continue;

            int noteTime = note.getTimeMs(bpm, beatsPerBar);

            // ノーツ時刻を過ぎたら即再生
            if (currentMs >= noteTime) {
                note.hit = true;
                sozaiManager->playSozai(note.inputId, 0);
            }
        }
    }
}

void NoteManager::draw() const {
    int elapsedMs = currentTimeMs;

    // 1小節の時間（ms）
    int barDurationMs = (60000 * beatsPerBar) / bpm;

    // Y方向スクロール速度（1小節分 = barHeightPx 移動）
    float scrollSpeedY = static_cast<float>(barHeightPx) / barDurationMs;

    // ノート描画
    for (const auto& note : notes) {
        // 小節内の位置を 0.0〜1.0 で算出
        float beatRatio = static_cast<float>(note.beat - 1) / beatsPerBar;
        float subRatio = static_cast<float>(note.subdivision - 1) / note.subdivisionCountPerBeat / beatsPerBar;
        float noteRatio = beatRatio + subRatio;

        int noteX = startX + static_cast<int>(noteRatio * barWidthPx);
        int noteY = baseY - static_cast<int>(elapsedMs * scrollSpeedY) + (note.bar - 1) * barHeightPx;

        if (noteY < -64 || noteY > Define::WIN_H * 0.25) continue;    // 画面外は描画しない


        // 星間飛行用の一時的な変換
        static const int remap[8] = { 0, 5, 1, 4, 2, 7, 3, 6 };

        // 変換してから使う
        int mappedId = remap[note.inputId % 8];

        DrawRotaGraph(noteX, noteY, 0.5f, 0.0f, noteImages[mappedId], TRUE);

        //DrawRotaGraph(noteX, noteY, 0.5f, 0.0f, noteImages[note.inputId % 8], TRUE);
    }

    // マーカー描画
    int markerBarIndex = elapsedMs / barDurationMs;
    int markerOffsetMs = elapsedMs % barDurationMs;
    float markerRatio = static_cast<float>(markerOffsetMs) / barDurationMs;

    int markerX = startX + static_cast<int>(markerRatio * barWidthPx);
    int markerY = baseY - static_cast<int>(elapsedMs * scrollSpeedY) + markerBarIndex * barHeightPx;

    DrawCircle(markerX, markerY, 10, GetColor(255, 0, 0), TRUE); // マーカー（赤）
}

void NoteManager::addNote(const Note& note) {
    notes.push_back(note);
}

void NoteManager::addTestNote(int bar, int beat, int subdivision) {
    Note note;
    note.bar = bar;
    note.beat = beat;
    note.subdivision = subdivision;
    note.subdivisionCountPerBeat = 4; // 必要ならここは可変に
    addNote(note);
}

void NoteManager::clearNotes() {
    notes.clear();
}

void NoteManager::startPlay() {
    //setStartTimeMs(Time::getIns()->getMilliseconds());
}

void NoteManager::setCurrentTimeMs(int time) {
    currentTimeMs = time;
}

const std::vector<Note>& NoteManager::getNotes() const {
    return notes;
}

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
    : bpm(bpm), beatsPerBar(beatsPerBar) {
    barDurationMs = (60000 * beatsPerBar) / bpm;
    barWidthPx = Define::WIN_W * 0.4;
    startX = Define::WIN_W * 0.3;

    sozaiManager = sozai;
    BGMHandle = -1;

    // ノート画像読み込み
    noteImages[0] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/down.png");
    noteImages[1] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/left.png");
    noteImages[2] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/up.png");
    noteImages[3] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/right.png");
    noteImages[4] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/buttonY.png");
    noteImages[5] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/buttonB.png");
    noteImages[6] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/buttonA.png");
    noteImages[7] = Image::getIns()->loadSamples("Assets/Sprites/images/Common/notes/buttonX.png");
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
    setCurrentTimeMs(GetSoundCurrentTime(BGMHandle));
    updateAutoPlay();
    return true;
}

void NoteManager::updateAutoPlay() {
    int currentMs = GetSoundCurrentTime(BGMHandle);

    constexpr int lookaheadMs = 50; // 先読み時間
    for (auto& note : notes) {
        if (note.hit) continue;

        int noteTime = note.getTimeMs(bpm, beatsPerBar);
        int delta = noteTime - currentMs;

        if (0 <= delta && delta <= lookaheadMs) {
            note.hit = true;

            // タイマーで音再生を予約
            std::thread([delta, inputId = note.inputId, this]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(delta));
                sozaiManager->playSozai(inputId, 0);
                }).detach();
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

        if (noteY < Define::WIN_H * 0.1 || noteY > Define::WIN_H * 0.35) continue;    // 画面外は描画しない

        DrawRotaGraph(noteX, noteY, 0.5f, 0.0f, noteImages[note.inputId % 8], TRUE);
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

#include <fstream>
#include <sstream>
#include <iostream>
#include "NoteManager.h"
#include <DxLib.h>
#include "Common/Time.h"
#include "System/Define.h"

NoteManager::NoteManager(int bpm, int beatsPerBar)
    : bpm(bpm), beatsPerBar(beatsPerBar) {
    barDurationMs = (60000 * beatsPerBar) / bpm;
    barWidthPx = Define::WIN_W * 0.4;
    startX = Define::WIN_W * 0.3;
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
    setCurrentTimeMs(Time::getIns()->getMilliseconds());
    return true;
}

void NoteManager::draw() const {
    int elapsedMs = currentTimeMs - startTimeMs;

    // 正確なY移動速度を計算（1小節分Y移動する時間に合わせる）
    const float scrollSpeedY = static_cast<float>(barHeightPx) / barDurationMs;
    // ノート描画
    for (const auto& note : notes) {
        int noteTimeMs = note.getTimeMs(bpm, beatsPerBar);
        float noteRatio = (note.beat - 1) / beatsPerBar + (note.subdivision - 1) / note.subdivisionCountPerBeat;
        int noteOffsetMs = barDurationMs * noteRatio;

        int noteX = startX + static_cast<int>(noteRatio * barWidthPx);
        int noteY = baseY - static_cast<int>(elapsedMs * scrollSpeedY) + note.bar * barHeightPx;

        DrawCircle(noteX, noteY, 10, GetColor(255, 255, 255), TRUE); // ノート（白）
    }

    // マーカー位置
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
    setStartTimeMs(Time::getIns()->getMilliseconds());
}

void NoteManager::setStartTimeMs(int time) {
    startTimeMs = time;
}

void NoteManager::setCurrentTimeMs(int time) {
    currentTimeMs = time;
}

const std::vector<Note>& NoteManager::getNotes() const {
    return notes;
}

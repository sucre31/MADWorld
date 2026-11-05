#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include "NoteManager.h"
#include <DxLib.h>
#include "Common/Time.h"
#include "System/Define.h"
#include "Common/Image.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

NoteManager::NoteManager(int bpm, int beatsPerBar, SozaiManager* sozai)
    : bpm(bpm), beatsPerBar(beatsPerBar) , playbackPool(3){
    timeBeginPeriod(1);
    barDurationMs = (60000 * beatsPerBar) / bpm;

    sozaiManager = sozai;
    BGMHandle = -1;

    // オートはデフォルトオフ
    useAutoPlay = true;
}

bool NoteManager::loadFromFile(const std::string& path) {

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open note file: " << path << std::endl;
        return false;
    }

    notes.clear();

    try {
        json j;
        file >> j;

        // "chart" 配列があるか確認
        if (j.contains("chart") && j["chart"].is_array()) {
            for (const auto& noteJson : j["chart"]) {
                Note note;

                // JSONから値を読み込む（見つからない場合はデフォルト値を設定）
                note.bar = noteJson.value("bar", 1);
                note.beat = noteJson.value("beat", 1);
                note.subdivision = noteJson.value("sub", 1);
                note.subdivisionCountPerBeat = noteJson.value("subCount", 4);
                note.inputId = noteJson.value("id", 0);
                note.soundIndex = noteJson.value("soundIndex", 0);

                notes.push_back(note);
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "JSON Parse Error in NoteManager: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Loaded " << notes.size() << " notes from " << path << std::endl;
    return true;
}

bool NoteManager::update() {
    setCurrentTimeMs((int)GetSoundCurrentTime(BGMHandle));
    if (useAutoPlay) {
        updateAutoPlay();
    }
    else {
        checkMissedNotes();
    }
    return true;
}

void NoteManager::updateAutoPlay() {
    if (useAutoPlay) {
        int currentMs = getCurrentTimeMs();

        for (auto& note : notes) {
            if (note.hit) continue;

            int noteTime = note.getTimeMs(bpm, beatsPerBar);

            // ノーツ時刻を過ぎたら即再生
            if (currentMs >= noteTime) {
                note.hit = true;
                note.judge = eJudge::PERFECT;
                perfectCount++;
                combo++;

                if (eventCallback) {
                    eventCallback(note);
                }
            }
        }
    }
}

void NoteManager::draw() const {
    // NoteUIManagerに移行
}

eJudge NoteManager::judgeInput(ePad pressedPad) {
    if (useAutoPlay) return eJudge::NONE;

    int currentMs = getCurrentTimeMs();
    const int JUDGE_PERFECT = 33;  // ±33ms
    const int JUDGE_GREAT = 66;    // ±66ms
    const int JUDGE_MISS = 130;    // ±130ms

    Note* closestNote = nullptr;
    int minDiff = 999999;

    // 一番近い未処理のノーツを探す
    for (auto& note : notes) {
        if (note.hit || note.missed) continue;
        // パッドのキーで判定しているけど、不安定かも？バグないか確認
        ePad expectedPad = sozaiManager->getMappedPad(note.inputId, note.soundIndex);
        if (expectedPad != pressedPad) continue;

        int noteTime = note.getTimeMs(bpm, beatsPerBar);
        int diff = std::abs(noteTime - currentMs);

        if (diff < minDiff && diff <= JUDGE_MISS) {
            minDiff = diff;
            closestNote = &note;
        }
    }

    if (closestNote) {
        closestNote->hit = true;
        if (minDiff <= JUDGE_PERFECT) {
            closestNote->judge = eJudge::PERFECT;
            perfectCount++;
            combo++;
        }
        else if (minDiff <= JUDGE_GREAT) {
            closestNote->judge = eJudge::GREAT;
            greatCount++;
            combo++;
        }
        else {
            closestNote->judge = eJudge::GOOD;
            goodCount++;
            combo++;
        }
        return closestNote->judge;
    }
    return eJudge::NONE;
}

void NoteManager::checkMissedNotes() {
    if (!isPlaying) return;

    int currentMs = getCurrentTimeMs();
    const int JUDGE_MISS = 130; // この時間を過ぎたらMiss

    for (auto& note : notes) {
        if (note.hit || note.missed) continue;

        int noteTime = note.getTimeMs(bpm, beatsPerBar);
        int diff = currentMs - noteTime; // ノーツまでの時間 

        // JUDGE_MISSを過ぎていたら見逃し判定にする
        if (diff > JUDGE_MISS) {
            note.missed = true;
            note.judge = eJudge::MISS;
            missCount++;
            combo = 0;
        }
    }
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
    isPlaying = true;
    playStartTimeMs = GetNowCount();
}

void NoteManager::setCurrentTimeMs(int time) {
    currentTimeMs = time;
}

const std::vector<Note>& NoteManager::getNotes() const {
    return notes;
}

#pragma once
#include "GameObject.h"
#include "Note.h"
#include <vector>

class NoteManager : public GameObject {
public:
    NoteManager(int bpm, int beatsPerBar);

    bool update() override;
    void draw() const override;

    // ファイルからノートを読み込む（仮形式）
    bool loadFromFile(const std::string& path);

    void addNote(const Note& note);
    void clearNotes();

    void startPlay();

    void setStartTimeMs(int time);
    void setCurrentTimeMs(int time);

    const std::vector<Note>& getNotes() const;

    void addTestNote(int bar, int beat, int subdivision);

private:
    std::vector<Note> notes;
    int bpm;
    int beatsPerBar;
    int startTimeMs = 0;
    int currentTimeMs = 0;
    int barDurationMs = 0;
    // 表示設定
    int barWidthPx = 600;   // 横幅（1小節）
    int barHeightPx = 100;  // 縦段の高さ（1小節）
    int startX = 100;
    int baseY = 200;
};

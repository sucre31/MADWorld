#pragma once
#include "GameObject.h"
#include "SozaiManager.h"
#include "System/PlayBackThreadPool.h"
#include "Note.h"
#include <vector>

class NoteManager : public GameObject {
public:
    NoteManager(int bpm, int beatsPerBar, SozaiManager* sozai);

    bool update() override;
    void draw() const override;

    // ファイルからノートを読み込む（仮形式）
    bool loadFromFile(const std::string& path);

    void addNote(const Note& note);
    void clearNotes();

    void startPlay();

    void setCurrentTimeMs(int time);

    const std::vector<Note>& getNotes() const;

    void addTestNote(int bar, int beat, int subdivision);

    void setBGMHandle(int soundHandle) { BGMHandle = soundHandle; }

    void updateAutoPlay();

private:
    SozaiManager* sozaiManager = nullptr;
    PlaybackThreadPool playbackPool;
    std::vector<Note> notes;
    int bpm;
    int beatsPerBar;
    int currentTimeMs = 0;
    int barDurationMs = 0;
    // 表示設定
    int barWidthPx = 700;   // 横幅（1小節）
    int barHeightPx = 70;  // 縦段の高さ（1小節）
    int startX = 100;
    int baseY = 100;
    int noteImages[8];
    int BGMHandle;      // 再生時間確認用
};

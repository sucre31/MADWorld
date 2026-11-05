#pragma once
#include <DxLib.h>
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

    void setUseAutoPlay(bool flag) { useAutoPlay = flag; }

    int getCurrentTimeMs() const {
        return currentTimeMs;
    }
    int getBpm() const { return bpm; }
    int getBeatsPerBar() const { return beatsPerBar; }

    eJudge judgeInput(ePad pressedPad);

    std::function<void(const Note&)> eventCallback;

    void checkMissedNotes();

    int getPerfectCount() const { return perfectCount; }
    int getGreatCount()   const { return greatCount; }
    int getGoodCount()    const { return goodCount; }
    int getMissCount()    const { return missCount; }
    int getCombo()        const { return combo; }

private:
    SozaiManager* sozaiManager = nullptr;
    PlaybackThreadPool playbackPool;
    std::vector<Note> notes;
    int bpm;
    int beatsPerBar;
    int currentTimeMs = 0;
    int barDurationMs = 0;
    int BGMHandle;      // 再生時間確認用
    bool useAutoPlay;
    int playStartTimeMs = 0;
    bool isPlaying = false;

    int perfectCount = 0;
    int greatCount = 0;
    int goodCount = 0;
    int missCount = 0;
    int combo = 0;
};

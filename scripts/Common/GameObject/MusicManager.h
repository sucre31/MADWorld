#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>

class MusicManager : public GameObject
{
public:
    MusicManager();
    ~MusicManager();
    bool update() override;
    void draw() const override;

    // 音楽ファイルをロード（nameで識別）
    bool LoadMusic(const std::string& name, const std::string& path);

    // 再生・制御
    void Play(const std::string& name, bool loop = true);
    void Stop();
    void Pause();
    void Resume();
    bool IsPlaying() const;

    int GetHandle() { return currentHandle; }

    // フェードアウト付き停止
    void FadeOut(int fadeTimeMs = 1000);

    int GetNowPlayingHandle() const;

private:
    std::unordered_map<std::string, int> bgmHandles;
    std::string currentMusicName;
    int currentHandle = -1;
    int pausedPosition = -1; // 再開用に記録
};

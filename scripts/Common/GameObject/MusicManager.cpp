#include "MusicManager.h"
#include "Sound.h"
#include <DxLib.h>
#include <iostream>

MusicManager::MusicManager() {}

MusicManager::~MusicManager() {
    Stop();
    for (const auto& pair : bgmHandles) {
        DeleteSoundMem(pair.second); // 明示的に破棄（Sound 側と分離して管理）
    }
    bgmHandles.clear();
}

bool MusicManager::LoadMusic(const std::string& name, const std::string& path) {
    int handle = Sound::getIns()->loadBGM(path.c_str());
    if (handle == -1) {
        std::cerr << "Failed to load BGM: " << path << std::endl;
        return false;
    }

    bgmHandles[name] = handle;
    return true;
}

bool MusicManager::update() {
    // 再生が終了したら currentHandle を無効にする
    if (currentHandle != -1 && CheckSoundMem(currentHandle) == 0) {
        currentHandle = -1;
        currentMusicName.clear();
    }

    return true; // 特に終了条件がなければ true
}

void MusicManager::draw() const {
    // デバッグ用
    if (!currentMusicName.empty()) {
        DrawFormatString(10, 10, GetColor(255, 255, 255), "Now Playing: %s", currentMusicName.c_str());
    }
}

void MusicManager::Play(const std::string& name, bool loop) {
    auto it = bgmHandles.find(name);
    if (it == bgmHandles.end()) {
        std::cerr << "BGM not found: " << name << std::endl;
        return;
    }

    if (currentHandle != -1) {
        StopSoundMem(currentHandle);
    }

    currentHandle = it->second;
    currentMusicName = name;

    int playType = loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_NORMAL;
    PlaySoundMem(currentHandle, playType);
}

void MusicManager::Stop() {
    if (currentHandle != -1) {
        StopSoundMem(currentHandle);
        currentHandle = -1;
        currentMusicName.clear();
    }
}

void MusicManager::Pause() {
    if (currentHandle != -1) {
        pausedPosition = GetCurrentPositionSoundMem(currentHandle);
        StopSoundMem(currentHandle); // 強制停止（再開用に位置保存）
    }
}

void MusicManager::Resume() {
    if (currentHandle != -1 && pausedPosition >= 0) {
        SetCurrentPositionSoundMem(pausedPosition, currentHandle);
        PlaySoundMem(currentHandle, DX_PLAYTYPE_BACK);
        pausedPosition = -1;
    }
}

bool MusicManager::IsPlaying() const {
    return currentHandle != -1 && CheckSoundMem(currentHandle) == 1;
}

void MusicManager::FadeOut(int fadeTimeMs) {
    if (currentHandle != -1) {
        const int steps = 10;
        for (int i = steps; i >= 0; --i) {
            ChangeVolumeSoundMem(255 * i / steps, currentHandle);
            WaitTimer(fadeTimeMs / steps);
        }
        Stop();
    }
}

std::string MusicManager::GetNowPlaying() const {
    return currentMusicName;
}

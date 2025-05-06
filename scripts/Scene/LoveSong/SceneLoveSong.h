#pragma once
#include "System/AbstractScene.h"
#include "Common/GameObject/MusicManager.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/GameObject/NoteManager.h"
class SceneLoveSong : public AbstractScene
{
public:
    SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneLoveSong() = default;
    void update() override;
    void draw() const override;
    void addReviveChar(std::string);
    void resetString();
private:
    void loadLoveSongSamples(); // 音楽のロード関数を追加
    // 初期化処理
    void initializeFont();      // フォント初期化
    void initializeMusic();     // 音楽の初期化
    void initializeResources(); // 画像リソースとMIDIの初期化
    void setSozaiPosNoBGM();    // 素材の位置設定(初期状態)
    void setSozaiPosPlay();    // 素材の位置設定(プレイ状態)
    MusicManager musicManager;
    SozaiManager sozaiManager;
    NoteManager noteManager;
    const int strSize = 74;
    bool movieTurnFlag;
    int musicIndex;
    bool isMusicPlay;
    int backGroundHandle;
    std::string stringRevive;
    int strIndex;
    const int sozaiNum = 16;
};


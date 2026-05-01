#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "System/AbstractScene.h"
#include "Common/GameObject/SozaiManager.h"
#include "Common/Camera/CameraStream.h"
#include "Common/Online/WSClient.h"
#include "Common/Online/WSDataHolder.h"
#include "Common/Particle.h"

class SceneAlice : public AbstractScene
{
public:
    SceneAlice(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneAlice();
    void update() override;
    void draw() const override;
private:
    struct RenderPlayer {
        std::string id;

        float x, y;          // 表示位置（補間後）
        float targetX, targetY; // サーバー位置
        float accel;
        float targetAccel;

        float lastSeenTime;
    };

    int imgSmall;
    int imgMiddle;
    int imgBig;

    void updateParticles(float dt);
    // シーンはインスタンスを管理するだけ
    SozaiManager sozaiManager;
    int aliceDrumHandle; // クラスかする
    bool isMusicPlay;
    CameraStream camera;
    WSDataHolder wsHolder;
    std::vector<NetPlayer> players;
    std::unordered_map<std::string, RenderPlayer> renderPlayers;
    std::unordered_map<std::string, ParticleEmitter> emitters;
    std::unordered_set<std::string> aliveIds;
};


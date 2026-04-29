#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <nlohmann/json.hpp>
#include "WSClient.h"
using json = nlohmann::json;

struct NetPlayer {
    std::string id;
    float x;
    float y;
    float accel;
    float heat;
};

enum class WSEvent {
    BURST,
    CONFIG,
};

class WSDataHolder {
public:
    WSDataHolder();
    ~WSDataHolder();

    void start();

    void update();

    bool consumeBurst();

    float getHeatRatio() const;
    float getHeatThreshold() const;

    std::vector<NetPlayer> getPlayers();

private:
    void connectTask();
    void handleMessage(const json& data);

private:
    WSClient ws;

    bool burst = false;
    float heatRatio = 0.0f;
    float heatThreshold = 1.0f;
    std::atomic<bool> burstEvent = false;

    std::thread connectThread;
    std::atomic<bool> running;
    std::atomic<bool> wsConnection;

    std::vector<NetPlayer> players;
    std::mutex mtx;
};
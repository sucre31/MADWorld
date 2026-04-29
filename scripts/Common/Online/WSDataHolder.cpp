#include "WSDataHolder.h"
#include <DxLib.h>

using json = nlohmann::json;

WSDataHolder::WSDataHolder()
    : running(true), wsConnection(false)
{
}

WSDataHolder::~WSDataHolder() {
    running = false;

    if (connectThread.joinable()) {
        connectThread.join();
    }
}

void WSDataHolder::start() {
    connectThread = std::thread(&WSDataHolder::connectTask, this);
}

void WSDataHolder::connectTask() {
    if (!running) return;

    if (ws.connect(L"madheavenwebsocket.onrender.com", L"/")) {
        ws.send(R"({"type": "REGISTER", "role": "game"})");
        wsConnection = true;
    }
    else {
        printfDx("Connection Failed.\n");
    }
}

void WSDataHolder::update() {
    if (!wsConnection) return;

    std::string msg;

    while (ws.pollMessage(msg)) {
        try {
            //printfDx("RAW: [%s]\n", msg.c_str());
            auto data = json::parse(msg);
            handleMessage(data);
        }
        catch (const std::exception& e) {
            printfDx("JSON Error: %s\n", e.what());
        }
        catch (...) {
            printfDx("Unknown JSON Error\n");
        }
    }
}

void WSDataHolder::handleMessage(const json& data) {
    if (!data.contains("type")) return;

    std::string type = data["type"];

    // ===== CONFIG =====
    if (type == "CONFIG") {
        if (data.contains("threshold")) {
            heatThreshold = data["threshold"].get<float>();
        }
        return;
    }

    // ===== UPDATE =====
    if (type == "UPDATE") {
        heatRatio = data.value("heatRatio", 0.0f);

        std::lock_guard<std::mutex> lock(mtx);

        players.clear();
        for (auto& p : data["details"]) {
            NetPlayer np;
            np.id = p["id"].get<std::string>();
            np.x = p["x"].get<float>();
            np.y = p["y"].get<float>();
            np.accel = p["accel"].get<float>();
            np.heat = p["heat"].get<float>();

            players.push_back(np);
        }
        return;
    }

    // ===== BURST単体メッセージの場合 =====
    if (type == "BURST") {
        burstEvent.store(true);
    }
}

bool WSDataHolder::consumeBurst() {
    if (burstEvent.exchange(false)) {
        return true;
    }
    return false;
}

float WSDataHolder::getHeatRatio() const {
    return heatRatio;
}

float WSDataHolder::getHeatThreshold() const {
    return heatThreshold;
}

std::vector<NetPlayer> WSDataHolder::getPlayers() {
    std::lock_guard<std::mutex> lock(mtx);
    return players;
}
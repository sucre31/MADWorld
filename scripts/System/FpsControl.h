#pragma once

#include "DxLib.h"
#include "System/Singleton.h"

class FpsControl final : public Singleton<FpsControl> {
private:
    LONGLONG prevTime = 0;
    double accumulator = 0.0;
    static constexpr double step = 1000000.0 / 60.0; // 1フレームあたりのマイクロ秒

    LONGLONG fpsTimer = 0;
    int fpsFrameCount = 0;
    float rFps = 0.0f;

    LONGLONG frameStartTime; // フレーム開始時刻
    const double targetFps = 1000.0; // 狙いたいFPS
    const double targetMicroSec = 1000000.0 / targetFps; // 1フレームあたりのマイクロ秒

    LONGLONG lastDrawTime;

    float deltaTime;

public:
    FpsControl();
    ~FpsControl() = default;

    bool Update();
    int getFrameRateNumber() const;
    bool isDrawFrame();
    bool isFrameChanged() const;
    void Draw();
    void Wait();
    float getDeltaTime() const { return deltaTime; }


    int FrameCount = 0;
    bool FrameChanged = false;
};
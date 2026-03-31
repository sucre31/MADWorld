#pragma once
#include "System/Singleton.h"
#include <DxLib.h>

class Time : public Singleton<Time> {
    friend class Singleton<Time>;

private:
    LONGLONG startCount = 0;
    LONGLONG prevCount = 0;
    double deltaTime = 0.0f;

    // DXLibのGetNowHiPerformanceCountは1秒間に1000000カウント（＝マイクロ秒精度）
    static constexpr double COUNTS_PER_SECOND = 1000000;
    static constexpr double MS_PER_COUNT = 1000.0 / COUNTS_PER_SECOND; // 1カウント当たりのミリ秒値


    Time() {
        prevCount = GetNowHiPerformanceCount();
    }

public:
    void update() {
        LONGLONG current = GetNowHiPerformanceCount();
        deltaTime = static_cast<float>(current - prevCount) / COUNTS_PER_SECOND;
        prevCount = current;
    }

    double getDeltaTime() const {
        return deltaTime;
    }

    // 起動からのミリ秒を取得
    int getMilliseconds() const {
        LONGLONG current = GetNowHiPerformanceCount();
        return static_cast<int>((current - startCount) * MS_PER_COUNT);
    }
};
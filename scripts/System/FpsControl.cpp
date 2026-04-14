#include "FpsControl.h"

FpsControl::FpsControl(){
    prevTime = GetNowHiPerformanceCount();
    accumulator = 0.0;
    FrameCount = 0;
    FrameChanged = false;

    fpsTimer = 0;
    fpsFrameCount = 0;
    rFps = 0.0f;
}

bool FpsControl::Update() {
    LONGLONG now = GetNowHiPerformanceCount();

    // 1. 前回の呼び出しからの経過時間（マイクロ秒）を計算
    LONGLONG diff = now - prevTime;
    prevTime = now;

    // 2. 蓄積変数に今回の経過時間を足す
    accumulator += (double)diff;

    FrameChanged = false;

    // 3. 蓄積時間が1フレーム分(約16666マイクロ秒)を超えていたら、ロジックを1回進める
    //printfDx("%lf\n", accumulator);
    if (accumulator >= step) {
        accumulator -= step; // 1フレーム分消費

        FrameChanged = true;
        FrameCount++;
    }

    // 4. FPS表示用の計測
    fpsTimer += diff;
    fpsFrameCount++;
    if (fpsTimer >= 1000000) { // 1秒経過
        rFps = (float)fpsFrameCount;
        fpsFrameCount = 0;
        fpsTimer -= 1000000;
    }

    return true;
}

bool FpsControl::isFrameChanged() const {
    return FrameChanged;
}

int FpsControl::getFrameRateNumber() const {
    return FrameCount;
}

void FpsControl::Draw() {
    DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS: %.1f", rFps);
}
#include "FpsControl.h"

FpsControl::FpsControl(){
    LONGLONG now = GetNowHiPerformanceCount();
    prevTime = now;
    frameStartTime = now;
    lastDrawTime = 0;
    accumulator = 0.0;
    FrameCount = 0;
    FrameChanged = false;

    fpsTimer = 0;
    fpsFrameCount = 0;
    rFps = 0.0f;
}

bool FpsControl::Update() {
    LONGLONG now = GetNowHiPerformanceCount();
    frameStartTime = now;

    // 1. 前回の呼び出しからの経過時間（マイクロ秒）を計算
    LONGLONG diff = now - prevTime;
    prevTime = now;

    deltaTime = (float)diff / 1000000.0f;

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

bool FpsControl::isDrawFrame() {
    LONGLONG now = GetNowHiPerformanceCount();
    // 前回の描画から 1/60秒 以上経っていたら描画フラグを立てる
    if (now - lastDrawTime >= 1000000.0 / 144.0) {
        lastDrawTime = now;
        return true;
    }
    return false;
}

int FpsControl::getFrameRateNumber() const {
    return FrameCount;
}

void FpsControl::Draw() {
    //DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS: %.1f", rFps);
}

// この関数をメインループの最後（ScreenFlipの後など）で呼ぶ
void FpsControl::Wait() {
    LONGLONG now;
    double elapsed;

    while (true) {
        now = GetNowHiPerformanceCount();
        elapsed = (double)(now - frameStartTime);

        // 目標時間まで残りどれくらいか
        double remaining = targetMicroSec - elapsed;

        if (remaining <= 0) break; // 目標時間に達したら抜ける

        // 1ms以上余裕があるなら、OSに処理を戻して休ませる（GPU/CPU負荷低減）
        if (remaining > 1000) {
            WaitTimer(1);
        }
        // 1ms未満なら、精度を出すためにあえてループで待つ（ビジーウェイト）
    }
}
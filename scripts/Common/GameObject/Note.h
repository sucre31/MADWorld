#pragma once

// ノートの構造体
struct Note {
    int bar;                   // 小節（1始まり）
    int beat;                  // 拍（1始まり）
    int subdivision;           // 拍の細分割位置（1始まり）
    int subdivisionCountPerBeat = 4; // 1拍あたりの細分割数（デフォルトは16分音符 = 4）
    int inputId;               // 判定に使う入力 or 素材ID
    bool hit = false;          // 判定済みかどうか

    // 発生時刻 (ms) を計算する関数
    int getTimeMs(int bpm, int beatsPerBar) const {
        const double beatDuration = 60000.0 / bpm; // 1拍あたりの時間(ms)
        double barOffset = (bar - 1) * beatsPerBar * beatDuration;
        double beatOffset = (beat - 1) * beatDuration;
        double subOffset = ((double)(subdivision - 1) / subdivisionCountPerBeat) * beatDuration;
        return static_cast<int>(barOffset + beatOffset + subOffset);
    }
};
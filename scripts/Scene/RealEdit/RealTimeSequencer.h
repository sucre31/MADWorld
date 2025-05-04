#pragma once
#include <vector>

class SozaiManager;

class RealTimeSequencer {
public:
	struct SozaiEvent {
		int timeMs;
		int sozaiIndex;
		int soundIndex;
		bool isMidi;
	};

	RealTimeSequencer();

	void update(SozaiManager& manager);
	void recordTrigger(int sozaiIndex, int soundIndex, bool isMidi);
	void resetStartTime();

	// ループ長設定と取得
	void setLoopLength(int ms);
	int getLoopLength() const;

	// BPM指定でループ長を自動設定（例：小節数 × 4拍）
	void setBPM(float bpm, int bars = 1); // bars = 小節数

	// 再生ON/OFF
	void setPlay(bool enable);
	bool isPlaying() const;

	void clear();

	// メトロノーム関連
	void setMetronome(bool enable);                         // メトロノームのオンオフ
	bool isMetronomeEnabled() const;                        // メトロノームがオンかどうか
	void setMetronomeSoundIndex(int index);
	void setAccentMetronomeSoundIndex(int index);


private:
	std::vector<SozaiEvent> events;
	int startTimeMs = 0;
	int loopLength = 4000; // デフォルト：4秒
	bool metronomeEnabled;  // メトロノーム有効フラグ
	bool playing = false;
	int metronomeSoundIndex; // メトロノーム音のインデックス
	int accentMetronomeSoundIndex;
	float bpm = 120.0f;
	int previousBeat = -1; // 前回の拍を記録して、重複再生を防ぐ
};

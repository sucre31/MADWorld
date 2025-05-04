#include "RealTimeSequencer.h"
#include "DxLib.h"
#include "SozaiManager.h"

RealTimeSequencer::RealTimeSequencer()
	: loopLength(0), startTimeMs(0), playing(false), metronomeEnabled(false), metronomeSoundIndex(0) {
}

void RealTimeSequencer::update(SozaiManager& manager) {
    if (!playing) return;

    int currentTime = (GetNowCount() - startTimeMs) % loopLength;

    for (const auto& ev : events) {
        if (ev.timeMs == currentTime) {
            manager.playSozai(ev.sozaiIndex, ev.soundIndex);
        }
    }

    // メトロノーム
    if (metronomeEnabled) {
        int beatTime = 60000 / bpm;
        int beatNumber = currentTime / beatTime;

        if (beatNumber != previousBeat) { // 拍が進んだら
            previousBeat = beatNumber;

            if (beatNumber % 4 == 0) {
                // アクセント（4拍目ごと）
                manager.playSozai(0, accentMetronomeSoundIndex);
            }
            else {
                // 通常の拍
                manager.playSozai(0, metronomeSoundIndex);
            }
        }
    }
}
void RealTimeSequencer::recordTrigger(int sozaiIndex, int soundIndex, bool isMidi) {
	int currentTime = (GetNowCount() - startTimeMs) % loopLength;
	events.push_back(SozaiEvent{ currentTime, sozaiIndex, soundIndex, isMidi });
}

void RealTimeSequencer::resetStartTime() {
	startTimeMs = GetNowCount();
}

void RealTimeSequencer::setLoopLength(int ms) {
	loopLength = ms;
}

int RealTimeSequencer::getLoopLength() const {
	return loopLength;
}

void RealTimeSequencer::setBPM(float newBpm, int bars) {
	bpm = newBpm;
	float beatsPerBar = 4.0f; // 4拍子
	float beatLengthMs = 60000.0f / bpm;
	loopLength = static_cast<int>(beatLengthMs * beatsPerBar * bars);
}

void RealTimeSequencer::setPlay(bool enable) {
	playing = enable;
}

bool RealTimeSequencer::isPlaying() const {
	return playing;
}

void RealTimeSequencer::clear() {
	events.clear();
}

void RealTimeSequencer::setMetronome(bool enable) {
	metronomeEnabled = enable;
}

bool RealTimeSequencer::isMetronomeEnabled() const {
	return metronomeEnabled;
}

void RealTimeSequencer::setMetronomeSoundIndex(int index) {
    accentMetronomeSoundIndex = index;
}

void RealTimeSequencer::setAccentMetronomeSoundIndex(int index) {
    accentMetronomeSoundIndex = index;
}
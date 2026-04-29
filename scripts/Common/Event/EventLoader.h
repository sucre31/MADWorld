#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "TimedEvent.h"
#include "ActionRegistry.h"

class EventLoader {
public:
	// JSONファイルからイベント読み込み
	static std::vector<TimedEvent> loadFromFile(
		const std::string& path,
		ActionRegistry& registry
	);

private:
	// bar / beat → 実数beat変換
	static double convertToBeat(int bar, int beat, int beatsPerBar = 4);
};
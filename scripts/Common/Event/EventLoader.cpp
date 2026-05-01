#include "EventLoader.h"
#include <fstream>
#include <Dxlib.h>

std::vector<TimedEvent> EventLoader::loadFromFile(
	const std::string& path,
	ActionRegistry& registry
) {
	std::vector<TimedEvent> events;

	std::ifstream ifs(path, std::ios::binary);
	if (!ifs.is_open()) {
		// 読めなかったら空で返す
		return events;
	}

	nlohmann::json j;
	ifs >> j;

	if (!j.contains("events")) {
		return events;
	}

	for (auto& item : j["events"]) {

		// 必須チェック
		if (!item.contains("bar") || !item.contains("beat") || !item.contains("type")) {
			continue;
		}

		int bar = item["bar"];
		double beat = item["beat"];

		TimedEvent e;
		e.beat = convertToBeat(bar, beat);

		// action生成（itemそのまま渡す）
		e.action = registry.create(item);

		if (e.action) {
			events.push_back(std::move(e));
		}
	}

	return events;
}

// 4/4前提
double EventLoader::convertToBeat(int bar, double beat, int beatsPerBar) {
	return (bar - 1) * beatsPerBar + (beat - 1.0);
}
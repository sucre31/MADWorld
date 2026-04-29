#include "ActionRegistry.h"

std::unique_ptr<IEventAction> ActionRegistry::create(const  nlohmann::json& j) {
	auto type = j["type"].get<std::string>();
	return creators[type](j);
}

void ActionRegistry::registerAction(const std::string& type, Creator c) {
	creators[type] = c;
}
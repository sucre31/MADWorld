#pragma once
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <memory>
#include <functional>
#include <string>
#include "IEventAction.h"


class ActionRegistry {
public:
	using Creator = std::function<std::unique_ptr<IEventAction>(const nlohmann::json&)>;

	std::unordered_map<std::string, Creator> creators;

	void registerAction(const std::string& type, Creator c);

	std::unique_ptr<IEventAction> create(const  nlohmann::json& j);
};
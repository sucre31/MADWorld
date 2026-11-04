#include "System/Parameter.h"
/*
@brief パラメータのセット
*/
void Parameter::SetInt(std::string& key, int val) {
	_intMap[key] = val;
}

/*
@brief パラメータの取得
*/
int Parameter::GetInt(std::string& key) const {
	auto it = _intMap.find(key);
	if (_intMap.end() == it) {
		return Error;
	}
	else {
		return it->second;
	}
}

/*
@brief パラメータのセット
*/
void Parameter::SetString(const std::string& key, const std::string& val) {
	_stringMap[key] = val;
}

/*
@brief パラメータの取得
*/
std::string Parameter::GetString(const std::string& key) const {
	auto it = _stringMap.find(key);
	if (_stringMap.end() == it) {
		return "";
	}
	else {
		return it->second;
	}
}
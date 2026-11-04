#pragma once

#include<string>
#include <map>

class Parameter
{
public:
    const static int Error = -1;
    Parameter() = default;
    virtual ~Parameter() = default;

    void SetInt(std::string& key, int val);
    int GetInt(std::string& key) const;

	void SetString(const std::string& key, const std::string& val);
	std::string GetString(const std::string& key) const;

private:
    std::map<std::string, int> _intMap;
	std::map<std::string, std::string> _stringMap;
};
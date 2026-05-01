#pragma once
#include <vector>
#include <memory>

class StatusWindow;


class StatusWindowManager
{
public:
	StatusWindowManager();
	~StatusWindowManager() = default;
	std::shared_ptr<StatusWindow> getWindowById(int id);
	void AddWindow(std::shared_ptr<StatusWindow> window);
private:
	std::vector<std::shared_ptr<StatusWindow>> windows;
};


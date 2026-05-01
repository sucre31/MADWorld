#include "StatusWindowManager.h"
#include "StatusWindow.h"


StatusWindowManager::StatusWindowManager() {

}

std::shared_ptr<StatusWindow> StatusWindowManager::getWindowById(int id) {

	if (id < windows.size()) {
		return windows[id];
	}
	return nullptr;
}

void StatusWindowManager::AddWindow(std::shared_ptr<StatusWindow> window) {
	windows.push_back(window);
}
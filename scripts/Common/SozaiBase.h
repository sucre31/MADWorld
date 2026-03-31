#pragma once
#include <unordered_map>
#include "Common/GameObject/SozaiManager.h"
class SozaiBase
{
public:
	virtual ~SozaiBase() = default;
	void setSozaiManager(SozaiManager* manager);
	void setActive(bool flag);
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void initSozai() = 0;
	virtual void setKey() = 0;
	virtual void resetKey();

protected:
	SozaiManager* sozaiManager = nullptr;
	bool isActive = false;

	virtual void setLayerFront();
	void setLayerBack();
	std::unordered_map<int, int> sozaiHandles;
	std::unordered_map<int, ePad> sozaiPads;
};


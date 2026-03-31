#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"

enum class DonesiaSozai
{
	Kawahara,
	Goto
};

enum class DonesiaSound
{
	In,
	Donesia
};

class DonesiaManager
{
public:
	DonesiaManager();
	void update();
	void draw() const;
	~DonesiaManager() = default;
	void setSozaiManager(SozaiManager* sozai);
	void initSozai();
	void setActive(bool flag);
private:
	void setLayerFront();
	void setLayerBack();
	void setKey();
	void resetKey();
	bool isActive;
	SozaiManager* sozaiManager;
	std::unordered_map<DonesiaSozai, int> sozaiHandles;
	std::unordered_map<DonesiaSound, ePad> sozaiPads;
};


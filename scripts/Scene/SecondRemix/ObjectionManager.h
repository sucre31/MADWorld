#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"

enum class ObjectionSozai
{
	Naruhodo,
	Mitsurugi,
	NaruhodoTable,
	MitsurugiTable,
	NaruhodoBack,
	MitsurugiBack
};

enum class ObjectionSound
{
	NaruhodoIdle,
	MitsurugiIdle,
	NaruhodoBass,
	MitsurugiBass,
	NaruhodoObjection,
	MitsurugiObjection,
	NaruhodoHoldIt,
	MitsurugiHoldIt,
	NaruhodoTakeThat,
	MitsurugiTakeThat
};


class ObjectionManager
{
public :
	ObjectionManager();
	void update();
	void draw() const;
	~ObjectionManager() = default;
	void setSozaiManager(SozaiManager* sozai);
	void initSozai();
	void setActive(bool flag);
private:
	void setKey();
	void resetKey();
	void setNaruhodoFront();
	void setMitsurugiFront();
	void setLayerBack();
	bool isActive = false; 
	SozaiManager* sozaiManager;
	std::unordered_map<ObjectionSozai, int> sozaiHandles;
	std::unordered_map<ObjectionSound, ePad> sozaiPads;
};


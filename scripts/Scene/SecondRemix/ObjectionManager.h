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
private:
	void setKey();
	void setNaruhodoFront();
	void setMitsurugiFront();
	SozaiManager* sozaiManager;
	std::unordered_map<ObjectionSozai, int> sozaiHandles;
	std::unordered_map<ObjectionSound, ePad> sozaiPads;
};


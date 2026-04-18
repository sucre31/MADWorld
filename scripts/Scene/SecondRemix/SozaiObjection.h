#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"
#include "Common/SozaiBase.h"
#include "Common/Online/WSClient.h"

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


class SozaiObjection : public SozaiBase
{
public :
	SozaiObjection();
	void update() override;
	void draw() const override;
	~SozaiObjection() = default;
	void initSozai() override;
private:
	WSClient ws;
	bool isNaruhodoTurn = false;
	void setKey() override;
	void setLayerFront() override;
	void setNaruhodoFront();
	void setMitsurugiFront();

	float heatThreshold = 0.6;

	bool wsConnection = false;
};


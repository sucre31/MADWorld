#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"
enum class DontacoSozai
{
	Dontacos,
	Drum
};

enum class DontacoSound
{
	DontacoIdle,
	DrumIdle,
	Don,
	Tacos,
	Tara,
	Don2,
	Tacos2,
	Do,
	Ta,
	DrumDon,
	DrumTacos,
	DrumTara,
	DrumDon2,
	DrumTacos2,
	DrumDo,
	DrumTa
};

class DontacoManager
{
public:
	DontacoManager();
	void update();
	void draw() const;
	~DontacoManager() = default;
	void setSozaiManager(SozaiManager* sozai);
	void initSozai();
	void setActive(bool flag);
private:
	void setLayerFront();
	void setLayerBack();
	void setKey();
	void resetKey();
	bool isActive;
	bool useDrum;
	SozaiManager* sozaiManager;
	std::unordered_map<DontacoSozai, int> sozaiHandles;
	std::unordered_map<DontacoSound, ePad> sozaiPads;
};

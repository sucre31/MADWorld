#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"
#include "Common/SozaiBase.h"

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

class SozaiDontaco : public SozaiBase
{
public:
	SozaiDontaco();
	void update() override;
	void draw() const override;
	~SozaiDontaco() = default;
	void initSozai() override;
	void trigger(int actionId) override;
private:
	void setKey() override;
	bool useDrum = false;
};

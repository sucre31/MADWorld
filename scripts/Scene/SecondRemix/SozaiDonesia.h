#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"
#include "Common/SozaiBase.h"

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

class SozaiDonesia : public SozaiBase
{
public:
	SozaiDonesia();
	void update() override;
	void draw() const override;
	~SozaiDonesia() = default;
	void initSozai() override;
	void trigger(int actionId) override;
private:
	void setKey() override;
};


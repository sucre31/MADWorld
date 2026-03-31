#pragma once
#include "Common/SozaiBase.h"

enum class ShuzoSozai
{
	Shuzo
};

enum class ShuzoSound
{
	Shizukada
};

class SozaiShuzo : public SozaiBase
{
public:
	SozaiShuzo();
	void update() override;
	void draw() const override;
	~SozaiShuzo() = default;
	void initSozai() override;
private:
	void setKey() override;
};


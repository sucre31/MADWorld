#pragma once
#include <unordered_map>
#include <string>
#include "Common/GameObject/SozaiManager.h"
#include "System/Define.h"
#include "Common/SozaiBase.h"

enum class SonyaSozai
{
	Sonya,
	Yasuna
};

enum class SonyaSound
{
	Hey,
	Sukiari,
	Tto,
	Hit
};

class SozaiSonya : public SozaiBase
{
public:
	SozaiSonya();
	void update() override;
	void draw() const override;
	~SozaiSonya() = default;
	void initSozai() override;
private:
	void setKey() override;
};

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

class SonyaManager : public SozaiBase
{
public:
	SonyaManager();
	void update() override;
	void draw() const override;
	~SonyaManager() = default;
	void initSozai() override;
private:
	void setKey() override;
};

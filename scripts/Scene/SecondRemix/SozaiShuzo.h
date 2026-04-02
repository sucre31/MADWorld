#pragma once
#include "Common/SozaiBase.h";
//#include "Common/Online/HttpClient.h"
#include "Common/Online/WSClient.h"
#include "System/Define.h";


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
	WSClient ws;
	void setKey() override;
	void initializeFont();
	int fontHandle;
	const int shoutMax = 3;
	int shoutCount = 0;

	int timer;
	int prevVote = 0;
};


#pragma once

#include <vector>
#include "Singleton.h"

class Sound final : public Singleton<Sound>
{
public:
	Sound();
	~Sound() = default;
	void load() {};
	void release();
	const int* getLoveSongSamples() { return loveSongSamples; }
	const int getLoveSong() { return loveSongHandle; }
	void loadLoveSongSamples();

private:
	int myLoadSoundMem(char*);
	int myLoadSoundMem(const char*);
	std::vector<int> sounds;
	int loveSongSamples[8]; // �n���h���ێ�(���I�Ɋm�ۂ�����������
	int loveSongHandle;
};


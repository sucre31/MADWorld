#pragma once

#include <vector>
#include "Singleton.h"

class Image final : public Singleton<Image>
{
public:
	Image();
	~Image() = default;
	void load() {};
	void release();
	void loadLoveSongResources();
	const int* getLoveSongMovie() { return movieGraphHandle; }
	const int getLoveSongBack() { return backGroundHandle; }
private:
	int myLoadGraph(char*);
	int myLoadGraph(const char*);
	int myLoadDivGraph(char* fileName, int n, int xn, int yn, int w, int h, int* buf);
	int myLoadDivGraph(const char* fileName, int n, int xn, int yn, int w, int h, int* buf);
	std::vector<int> images;
	int screenHandle;
	int movieGraphHandle[8];
	int backGroundHandle;
};


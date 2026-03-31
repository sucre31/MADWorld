#include <Dxlib.h>
#include "SozaiShuzo.h"

SozaiShuzo::SozaiShuzo() {
	sozaiPads[(int)ShuzoSound::Shizukada] = ePad::A;
	initializeFont();
}

void SozaiShuzo::update() {
	if (isActive) {
		if (Pad::getIns()->get(sozaiPads[(int)ShuzoSound::Shizukada]) == 1) {
			shoutCount++;
		}
	}
}

void SozaiShuzo::draw() const{
	if (isActive) {
		DrawFormatStringToHandle(165, Define::WIN_H - 85, GetColor(255, 255, 255), fontHandle, "残り%d回", shoutMax - shoutCount);
	}
}

void SozaiShuzo::initializeFont() {
	fontHandle = CreateFontToHandle("MS UI Gothic", 75, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 6);
	SetFontSpaceToHandle(-10, fontHandle);
}

void SozaiShuzo::initSozai() {
	sozaiHandles[(int)ShuzoSozai::Shuzo] =
		sozaiManager->makeSozai("", "Assets/Sprites/movie/shuzo/shizukada.mp4", (Define::WIN_W / 2.0), (Define::WIN_H / 2.0));
	sozaiManager->addSound(sozaiHandles[(int)ShuzoSozai::Shuzo], "Assets/Sounds/shuzo/shizukada.wav");

	for (auto& pair : sozaiHandles)
	{
		int handle = pair.second;
		sozaiManager->setReverseFlag(handle, false);
		sozaiManager->setSozaiEx(handle, 2.0);
	}
}

int SozaiShuzo::getVoteCount() {
	std::string res = http.get("http://localhost:3000/count");

	if (!res.empty()) {
		int voteCount = std::stoi(res);
	}

	return 0;
}

void SozaiShuzo::setKey() {
	sozaiManager->setSozaiKey(sozaiHandles[(int)ShuzoSozai::Shuzo], sozaiPads[(int)ShuzoSound::Shizukada], 1);
}
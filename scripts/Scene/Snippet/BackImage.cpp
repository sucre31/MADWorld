#include <Dxlib.h>

#include "BackImage.h"
#include "System/Define.h"
#include "SnippetGameManager.h"

BackImage::BackImage() {
	AnimeNum = 0;
	tmpScreenHandle = MakeScreen(Define::WIN_W, Define::WIN_H, FALSE);;
}

bool BackImage::update() {
	bool frameChack = snippetGameManager->getFpsIns()->isFrameChanged();
	if (frameChack) {
		deley++;
		if (deley % 10 == 0) {
			AnimeNum = (++AnimeNum) % 14;
		}
	}
	return true;
}

void BackImage::draw() const {
	SetDrawScreen(tmpScreenHandle);
	ClearDrawScreen();
	DrawRotaGraph(160, 90, 1.25, 0, snippetImage->getBackgroundsA()[AnimeNum], TRUE);
	GraphFilter(tmpScreenHandle, DX_GRAPH_FILTER_GAUSS, 16, 400);
	GraphFilter(tmpScreenHandle, DX_GRAPH_FILTER_GAUSS, 16, 1200);
	SetDrawScreen(snippetImage->getScreenHandle());
	DrawGraph(0, 0, tmpScreenHandle, TRUE);
}

void BackImage::drawSecond() const {
	DrawGraph(0, 0, snippetImage->getBeltImage2(), TRUE);
	DrawGraph(0, 160, snippetImage->getBeltImage(), TRUE);
}
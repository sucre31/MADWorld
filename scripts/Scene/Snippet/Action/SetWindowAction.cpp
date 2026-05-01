#include "SetWindowAction.h"
#include "Scene/Snippet/Enemy.h"


void SetWindowAction::execute() {
	switch (soundType) {
	case 0:
		// プレイヤーのターン
		PlaySoundMem(snippetSound->getBattleSE()[1], DX_PLAYTYPE_BACK);
		break;
	case 1:
		// 敵のターン
		//PlaySoundMem(snippetSound->getBattleSE()[6], DX_PLAYTYPE_BACK);
		break;
	case 2:
		// 敵のpsi
		PlaySoundMem(snippetSound->getBattleSE()[7], DX_PLAYTYPE_BACK);
		break;
	case 3:
		// 状態異常
		PlaySoundMem(snippetSound->getBattleSE()[8], DX_PLAYTYPE_BACK);
		break;
	}
	window->setMessage(msg);
}
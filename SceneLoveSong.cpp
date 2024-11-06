#include <DxLib.h>
#include "Sound.h"
#include "Image.h"
#include "Define.h"
#include "Keyboard.h"
#include "Pad.h"
#include "SceneLoveSong.h"


SceneLoveSong::SceneLoveSong(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	// フォント設定
	ChangeFont("DragonQuestFC");
	SetFontSpace(3);
	SetFontSize(48);
	SetFontThickness(1);

	isMusicPlay = false;
	currentSoundIndex = 0;
	strIndex = 1;
	stringRevive = "＊";
	Sound::getIns()->loadLoveSongSamples();
	Image::getIns()->loadLoveSongResources();
}

void SceneLoveSong::update()
{
	if (Pad::getIns()->get(ePad::L) == 1) {
		// 音楽再生
		if (!isMusicPlay) {
			PlaySoundMem(Sound::getIns()->getLoveSong(), DX_PLAYTYPE_LOOP, TRUE);
			isMusicPlay = true;
		}
		else {
			StopSoundMem(Sound::getIns()->getLoveSong());
			isMusicPlay = false;
		}
	}
	if (Pad::getIns()->get(ePad::down) == 1) {
		playSampleSound(0);
		addReviveChar("ぱ");
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		playSampleSound(1);
		addReviveChar("わ");
		addReviveChar("い");
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		playSampleSound(2);
		addReviveChar("ち");
		addReviveChar("ゅ");
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		playSampleSound(3);
		addReviveChar("き");
		addReviveChar("ゅ");
		addReviveChar("ん");
	}
	if (Pad::getIns()->get(ePad::Y) == 1) {
		playSampleSound(4);
		addReviveChar("は");
		addReviveChar("あ");
		addReviveChar("ん");
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		playSampleSound(5);
		addReviveChar("お");
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		playSampleSound(6);
		addReviveChar("が");
	}
	if (Pad::getIns()->get(ePad::X) == 1) {
		playSampleSound(7);
		addReviveChar("し");
		addReviveChar("ゃ");
	}
	if (Pad::getIns()->get(ePad::start) == 1) {
		// メニューに戻る
		Parameter parameter;
		const bool stackClear = true;
		StopSoundMem(Sound::getIns()->getLoveSong());
		// ここに直接書くんじゃなくて関数用意すべきかな
		Sound::getIns()->release();
		Image::getIns()->release();
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}
}

void SceneLoveSong::playSampleSound(int num) {
	StopSoundMem(Sound::getIns()->getLoveSongSamples()[currentSoundIndex]);
	PlaySoundMem(Sound::getIns()->getLoveSongSamples()[num], DX_PLAYTYPE_BACK);
	currentSoundIndex = num;
	SeekMovieToGraph(Image::getIns()->getLoveSongMovie()[num], 0);
	PlayMovieToGraph(Image::getIns()->getLoveSongMovie()[num]);
}

/*
@brief ワイド文字（ひらがな）を受け取って末尾の文字に追加
*/
void SceneLoveSong::addReviveChar(std::string mes) {
	if (strIndex <= strSize - 1) {
		// ひらがななので2byte分消す 不具合起きる可能性あるかも
		// あと一文字(2byte)しか引数に取らないようにすべき
		if (strIndex % 14 == 3 || strIndex % 14 == 8) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "　　＊";
			strIndex+=3;
		}
		else if (strIndex == 70) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "　＊";
			strIndex += 2;
		}
		else if (strIndex == 74) {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes;
			strIndex += 2;
		}
		else {
			stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "＊";
			strIndex++;
		}
	}
	else {
		stringRevive.erase(0);
		strIndex = 1;
		stringRevive = stringRevive.substr(0, (strIndex - 1) * 2) + mes + "＊";
		strIndex++;
	}
}

void SceneLoveSong::draw() const
{
	DrawGraph(0, 0, Image::getIns()->getLoveSongBack(), FALSE);
	DrawGraph(400, 400, Image::getIns()->getLoveSongMovie()[currentSoundIndex], FALSE);
	DrawString(400, 30, "ふっかつのじゅもんを いれてください", GetColor(255, 255, 255));

	// じゅもん描画
	int strLength = strIndex*2;
	for (int i = 0; i < 5; i++) {
		if (i == 4) {
			if (strLength > i * 28) {
				DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 36).c_str(), GetColor(255, 255, 255));
				if (strLength < (i + 1) * 28) {
					// 文字が入っている最後の行
					break;
				}
			}
		}
		else {
			if (strLength > i * 28) {
				DrawString(454, 81 + 51 * i, stringRevive.substr(i * 28, 28).c_str(), GetColor(255, 255, 255));
				if (strLength < (i + 1) * 28) {
					// 文字が入っている最後の行
					break;
				}
			}
		}
	}
}
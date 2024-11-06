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
	}
	if (Pad::getIns()->get(ePad::left) == 1) {
		playSampleSound(1);
	}
	if (Pad::getIns()->get(ePad::up) == 1) {
		playSampleSound(2);
	}
	if (Pad::getIns()->get(ePad::right) == 1) {
		playSampleSound(3);
	}
	if (Pad::getIns()->get(ePad::Y) == 1) {
		playSampleSound(4);
	}
	if (Pad::getIns()->get(ePad::B) == 1) {
		playSampleSound(5);
	}
	if (Pad::getIns()->get(ePad::A) == 1) {
		playSampleSound(6);
	}
	if (Pad::getIns()->get(ePad::X) == 1) {
		playSampleSound(7);
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

void SceneLoveSong::draw() const
{
	DrawGraph(0, 0, Image::getIns()->getLoveSongBack(), FALSE);
	DrawGraph(400, 400, Image::getIns()->getLoveSongMovie()[currentSoundIndex], FALSE);
	DrawString(400, 30, "ふっかつのじゅもんを いれてください", GetColor(255, 255, 255));
	DrawString(454, 81, "ぱっが　　っがっ　　がっがが", GetColor(255, 255, 255));
	DrawString(454, 132, "ががが　　ががが　　はがっは", GetColor(255, 255, 255));
	DrawString(454, 183, "きゅき　　ゅんき　　ゅはおお", GetColor(255, 255, 255));
	DrawString(454, 234, "おおお　　はきゅ　　んきゅき", GetColor(255, 255, 255));
	DrawString(454, 285, "ゅちゅ　　きゅん　　はん＊", GetColor(255, 255, 255));
}
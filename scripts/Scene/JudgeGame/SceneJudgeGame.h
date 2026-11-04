#pragma once
#include "System/AbstractScene.h"

class SceneJudgeGame : public AbstractScene
{
	// jsonベースで譜面・画面配置などの情報を読み込み、
	// 任意のリズムゲームをプレイできるシーン
	// 一旦楽曲・素材情報をjsonで読み込むところを作る
	// その後、譜面に合わせて再生や判定を作っていく
public:
	SceneJudgeGame(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~SceneJudgeGame() = default;
	void update() override;
	void draw() const override;
private:

};


#include "SceneJudgeGame.h"

SceneJudgeGame::SceneJudgeGame(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	// パラメータからjsonファイルのパスを取得して譜面・素材情報を読み込む
	std::string jsonFilePath;
	jsonFilePath = parameter.GetString("jsonFilePath");
}

void SceneJudgeGame::update() {

}

void SceneJudgeGame::draw() const {
}
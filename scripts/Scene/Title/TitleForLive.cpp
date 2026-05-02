#include "TitleForLive.h"

#include <DxLib.h>
#include "System/Pad.h"
#include "Common/Image.h"
#include <vector>
#include <string>

// =========================
// メニュー構造体
// =========================
struct MenuItem {
    std::string name;
    eScene nextScene;
};

// =========================
// コンストラクタ
// =========================
TitleForLive::TitleForLive(IOnSceneChangedListener* impl, const Parameter& parameter)
    : AbstractScene(impl, parameter)
{
    ChangeFont("AR Pゴシック体S");
    SetFontSpace(1);
    SetFontSize(72);
    SetFontThickness(1);

    selectNum = 0;

    // 背景（シンプル）
    bgHandle = Image::getIns()->loadSamples("Assets/Sprites/images/title/titleScreen.png");

    // メニュー定義
    menu = {
        {"Scene A", eScene::Alice},
        {"Scene B", eScene::RobotSampler},
        {"Scene C", eScene::SecondRemix},
        {"Scene D", eScene::Snippet},
        {"Exit",    eScene::Opening} // Exitだけ特別扱いでもOK
    };
}

// =========================
// 更新
// =========================
void TitleForLive::update()
{
    int up = Pad::getIns()->get(ePad::up);
    int down = Pad::getIns()->get(ePad::down);

    // 上
    if (up == 1) {
        selectNum = (selectNum + menu.size() - 1) % menu.size();
    }

    // 下
    if (down == 1) {
        selectNum = (selectNum + 1) % menu.size();
    }

    // 決定
    if (Pad::getIns()->get(ePad::A) == 1) {
        Parameter parameter;

        if (menu[selectNum].name == "Exit") {
            DxLib_End();
            return;
        }

        _implSceneChanged->onSceneChanged(
            menu[selectNum].nextScene,
            parameter,
            true
        );
    }
}

// =========================
// 描画
// =========================
void TitleForLive::draw() const
{
    // 背景
    //DrawGraph(0, 0, bgHandle, FALSE);

    int baseX = 600;
    int baseY = 250;
    int spacing = 120;

    for (int i = 0; i < menu.size(); i++) {
        int y = baseY + spacing * i;

        if (i == selectNum) {
            // 選択中：背景を描く
            DrawBox(baseX - 20, y - 10, baseX + 500, y + 80, GetColor(200, 200, 200), TRUE);

            // 文字（黒）
            DrawString(baseX, y, menu[i].name.c_str(), GetColor(0, 0, 0));
        }
        else {
            // 非選択（白）
            DrawString(baseX, y, menu[i].name.c_str(), GetColor(255, 255, 255));
        }
    }

    // タイトル的なもの（シンプル）
    DrawString(50, 50, "SCENE SELECT", GetColor(255, 255, 255));
}
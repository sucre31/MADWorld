#include "System/Looper.h"
#include "Scene/Opening/OpeningScene.h"
#include "Scene/Title/TitleScene.h"
#include "Scene/Title/TitleForLive.h"
#include "Scene/Option/SceneOption.h"
#include "Scene/LoveSong/SceneLoveSong.h"
#include "Scene/Alice/SceneAlice.h"
#include "Scene/LightPlane/SceneLightPlane.h"
#include "Scene/MainMenu/SceneMainMenu.h"
#include "Scene/Dontaco/SceneDontaco.h"
#include "Scene/Sonya/VsSonya.h"
#include "Scene/StarGuitar/SceneStarguitar.h"
#include "Scene/Kajioh/SceneKajioh.h"
#include "Scene/SeikanHikou/SceneSeikanHikou.h"
#include "Scene/Snippet/SceneSnippet.h"
#include "Scene/RealEdit/SceneRealEdit.h"
#include "Scene/Pizza/ScenePizza.h"
#include "Scene/SecondRemix/SceneSecondRemix.h"
#include "Scene/RobotSampler/SceneRobot.h"
#include "System/Pad.h"
#include "System/MIDI.h"
#include "Common/Image.h"
#include "Common/Sound.h"
#include "Common/Time.h"

using namespace std;

Looper::Looper()
{
    screenRate = Define::WIN_EX;
    Parameter parameter;
    _sceneStack.push(make_shared<OpeningScene>(this, parameter)); //タイトル画面シーンを作ってpush
    useDebug = false;
}
/*!
@brief スタックのトップのシーンの処理をする
*/
bool Looper::loop() const
{
    int start = GetNowCount();

    Keyboard::getIns()->update();   //キーボードの更新
    Pad::getIns()->update();        //ジョイパッドの更新
    MIDI::getIns()->update();
    Time::getIns()->update();
    FpsControl::getIns()->Update();
    _sceneStack.top()->update();    //スタックのトップのシーンを更新

    if (FpsControl::getIns()->isDrawFrame()) {
        ClearDrawScreen();
        _sceneStack.top()->draw();      //スタックのトップのシーンを描画
        FpsControl::getIns()->Draw();
        //最後に画面の倍率に合わせて描画
        SetDrawScreen(DX_SCREEN_BACK);
        ScreenFlip();
    }

    

    FpsControl::getIns()->Wait();

    // デバッグ用表示
    if (useDebug) {
        int end = GetNowCount();
        if (end - start > 5) {
            printfDx("heavy frame: %d ms\n", end - start);
        }
    }
    return true;
}

/*!
@brief シーン変更(各シーンからコールバックされる)
@param scene 変更するシーンのenum
@param parameter 前のシーンから引き継ぐパラメータ
@param stackClear 現在のシーンのスタックをクリアするか
*/
void Looper::onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear)
{

    if (stackClear) {
        while (!_sceneStack.empty()) {
            _sceneStack.pop();
        }
    }
    switch (scene) {
    case Opening:
        _sceneStack.push(make_shared<OpeningScene>(this, parameter));
        break;
    case Title:
        _sceneStack.push(make_shared<TitleScene>(this, parameter));
        break;
    case Option:
        _sceneStack.push(make_shared<SceneOption>(this, parameter));
        break;
    case MainMenu:
        _sceneStack.push(make_shared<SceneMainMenu>(this, parameter));
        break;
    case LoveSong:
        _sceneStack.push(make_shared<SceneLoveSong>(this, parameter));
        break;
    case Alice:
        _sceneStack.push(make_shared<SceneAlice>(this, parameter));
        break;
    case LightPlane:
        _sceneStack.push(make_shared<SceneLightPlane>(this, parameter));
        break;
    case Dontaco:
        _sceneStack.push(make_shared<SceneDontaco>(this, parameter));
        break;
    case Sonya:
        _sceneStack.push(make_shared<VsSonya>(this, parameter));
        break;
    case Starguitar:
        _sceneStack.push(make_shared<SceneStarguitar>(this, parameter));
        break;
    case Kajioh:
        _sceneStack.push(make_shared<SceneKajioh>(this, parameter));
        break;
    case Seikan:
        _sceneStack.push(make_shared<SceneSeikanHikou>(this, parameter));
        break;
    case Snippet:
        _sceneStack.push(make_shared<SceneSnippet>(this, parameter));
        break;
    case RealEdit:
        _sceneStack.push(make_shared<SceneRealEdit>(this, parameter));
        break;
    case Pizza:
        _sceneStack.push(make_shared<ScenePizza>(this, parameter));
        break;
    case SecondRemix:
        _sceneStack.push(make_shared<SceneSecondRemix>(this, parameter));
        break;
    case RobotSampler:
        _sceneStack.push(make_shared<SceneRobot>(this, parameter));
        break;
    case TitleLive:
        _sceneStack.push(make_shared<TitleForLive>(this, parameter));
        break;
    //default:
    //    ERR("存在しないシーン");
    //    break;
    }
}

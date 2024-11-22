#include "Looper.h"
#include "OpeningScene.h"
#include "TitleScene.h"
#include "SceneOption.h"
#include "SceneLoveSong.h"
#include "SceneAlice.h"
#include "SceneLightPlane.h"
#include "SceneMainMenu.h"
//#include "Error.h"
//#include "Macro.h"
#include "Keyboard.h"
#include "Pad.h"
#include "MIDI.h"
#include "Image.h"
#include "Sound.h"

using namespace std;

Looper::Looper()
{
    screenRate = Define::WIN_EX;

    //Image::getIns()->load();

    Parameter parameter;
    //_fps = make_shared<FpsControl>();
    _sceneStack.push(make_shared<OpeningScene>(this, parameter)); //�^�C�g����ʃV�[���������push
    _fps = new FpsControl();
    //GameManager::getIns()->setFpsIns(_fps);
}
/*!
@brief �X�^�b�N�̃g�b�v�̃V�[���̏���������
*/
bool Looper::loop() const
{
    //SetDrawScreen(Image::getIns()->getScreenHandle());
    ClearDrawScreen();

    Keyboard::getIns()->update();   //�L�[�{�[�h�̍X�V
    Pad::getIns()->update();        //�W���C�p�b�h�̍X�V
    MIDI::getIns()->update();
    _sceneStack.top()->update();    //�X�^�b�N�̃g�b�v�̃V�[�����X�V
    _sceneStack.top()->draw();      //�X�^�b�N�̃g�b�v�̃V�[����`��
    _fps->Update();
    _fps->Draw();
    _fps->Wait();

    //�Ō�ɉ�ʂ̔{���ɍ��킹�ĕ`��
    SetDrawScreen(DX_SCREEN_BACK);
    //DrawExtendGraph(0, 0, (Define::WIN_W * screenRate), (Define::WIN_H * screenRate), Image::getIns()->getScreenHandle(), FALSE);
    return true;
}

/*!
@brief �V�[���ύX(�e�V�[������R�[���o�b�N�����)
@param scene �ύX����V�[����enum
@param parameter �O�̃V�[����������p���p�����[�^
@param stackClear ���݂̃V�[���̃X�^�b�N���N���A���邩
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
    //default:
    //    ERR("���݂��Ȃ��V�[��");
    //    break;
    }
}

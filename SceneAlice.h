#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
class SceneAlice : public AbstractScene
{
public:
    SceneAlice(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneAlice() = default; // �f�X�g���N�^�����厖 ��Œ���
    void update() override;
    void draw() const override;
private:
    // �V�[���̓C���X�^���X���Ǘ����邾��
    SozaiManager sozaiManager;
    int aliceDrumHandle; // �N���X������
    bool isMusicPlay;
};


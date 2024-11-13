#pragma once
#include "AbstractScene.h"
#include "SozaiManager.h"
#include "BackGround.h"

class SceneLightPlane : public AbstractScene
{
public:
    SceneLightPlane(IOnSceneChangedListener* impl, const Parameter& parameter);
    virtual ~SceneLightPlane() = default; // �f�X�g���N�^�����厖 ��Œ���
    void update() override;
    void draw() const override;
private:
    // �V�[���̓C���X�^���X���Ǘ����邾��
    SozaiManager sozaiManager;
    BackGround backGround;
};


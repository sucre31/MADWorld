#include <Dxlib.h>
#include "Sound.h"

Sound::Sound() {
}

/*
@brief ����t�@�C���̃��[�h
*/
void Sound::loadLoveSongSamples() {
    loveSongSamples[0] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample0.wav");
    loveSongSamples[1] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample1.wav");
    loveSongSamples[2] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample2.wav");
    loveSongSamples[3] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample3.wav");
    loveSongSamples[4] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample4.wav");
    loveSongSamples[5] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample5.wav");
    loveSongSamples[6] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample6.wav");
    loveSongSamples[7] = myLoadSoundMem("Assets/Sounds/LoveSong/LoveSample7.wav");
}

/*!
@brief ���܂Ń��[�h�����������������
*/
void Sound::release()
{
    const int size = sounds.size();
    for (int i = 0; i < size; i++) {
        DeleteSoundMem(sounds[i]);
    }
    sounds.clear();
}

/*!
@brief LoadSoundMem�����āA�����̃n���h���������o�ϐ��ɒǉ�����
*/
int Sound::myLoadSoundMem(char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}

/*!
@brief LoadSoundMem�����āA�����̃n���h���������o�ϐ��ɒǉ�����
*/
int Sound::myLoadSoundMem(const char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}
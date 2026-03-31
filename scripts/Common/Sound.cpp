#include <Dxlib.h>
#include "Sound.h"

Sound::Sound() {
}


/*
@brief 文字列を受け取りロード
*/
int Sound::loadSamples(const char* fileName) {
    int ret = myLoadSoundMem(fileName);
    return ret;
}

/*
@brief 文字列を受け取りロード
*/
int Sound::loadBGM(const char* fileName) {
    SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
    int ret = myLoadSoundMem(fileName);
    SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
    return ret;
}


/*!
@brief 今までロードした音声を解放する
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
@brief LoadSoundMemをして、かつそのハンドルをメンバ変数に追加する
*/
int Sound::myLoadSoundMem(char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}

/*!
@brief LoadSoundMemをして、かつそのハンドルをメンバ変数に追加する
*/
int Sound::myLoadSoundMem(const char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}
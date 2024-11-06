#include <DxLib.h>
#include "Image.h"
#include "Define.h"

Image::Image()
{
    screenHandle = MakeScreen(Define::WIN_W, Define::WIN_H, FALSE);
}

/*
@brief �ӂ����̂������p���\�[�X
*/
void Image::loadLoveSongResources() {
    movieGraphHandle[0] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall0.avi");
    movieGraphHandle[1] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall1.avi");
    movieGraphHandle[2] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall2.avi");
    movieGraphHandle[3] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall3.avi");
    movieGraphHandle[4] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall4.avi");
    movieGraphHandle[5] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall5.avi");
    movieGraphHandle[6] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall6.avi");
    movieGraphHandle[7] = myLoadGraph("Assets/sprites/movie/LoveMovieSmall7.avi");
    backGroundHandle = myLoadGraph("Assets/sprites/images/LoveSongBack.png");
}

/*!
@brief ���܂Ń��[�h�����摜���������
*/
void Image::release()
{
    const int size = images.size();
    for (int i = 0; i < size; i++) {
        DeleteGraph(images[i]);
    }
    images.clear();
}


/*!
@brief LoadGraph�����āA�����̃n���h���������o�ϐ��ɒǉ�����
*/
int Image::myLoadGraph(char* fileName)
{
    int ret = LoadGraph(fileName);
    images.push_back(ret);
    return ret;
}

/*!
@brief LoadGraph�����āA�����̃n���h���������o�ϐ��ɒǉ�����
*/
int Image::myLoadGraph(const char* fileName)
{
    int ret = LoadGraph(fileName);
    images.push_back(ret);
    return ret;
}

/*!
@brief LoadDivGraph�����āA�����̃n���h���������o�ϐ��ɒǉ�����
*/
int Image::myLoadDivGraph(char* fileName, int n, int xn, int yn, int w, int h, int* buf)
{
    int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
    for (int i = 0; i < n; i++) {
        images.push_back(buf[i]);
    }
    return ret;
}

int Image::myLoadDivGraph(const char* fileName, int n, int xn, int yn, int w, int h, int* buf)
{
    int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
    for (int i = 0; i < n; i++) {
        images.push_back(buf[i]);
    }
    return ret;
}
#include <DxLib.h>
#include "SnippetImage.h"
#include "System/Define.h"

SnippetImage::SnippetImage()
{
    screenHandle = MakeScreen(Define::WIN_W, Define::WIN_H, FALSE);
    SetTransColor(50, 78, 91);
    backImage = myLoadGraph("Assets/Sprites/images/Snippet/backImage.png");
    windowImage = myLoadGraph("Assets/Sprites/images/Snippet/window.png");
    beltImage = myLoadGraph("Assets/Sprites/images/Snippet/belt.png");
    beltImage2 = myLoadGraph("Assets/Sprites/images/Snippet/belt2.png");
    hitImage[0] = myLoadGraph("Assets/Sprites/images/Snippet/Battle/hit.png");
    hitImage[1] = myLoadGraph("Assets/Sprites/images/Snippet/Battle/hit2.png");
    EnemyImage[0] = myLoadGraph("Assets/Sprites/images/Snippet/Enemy/batty.png");
    EnemyImage[1] = myLoadGraph("Assets/Sprites/images/Snippet/Enemy/PigMask.png");
    EnemyImage[2] = myLoadGraph("Assets/Sprites/images/Snippet/Enemy/Spider!.png");
    EnemyImage[3] = myLoadGraph("Assets/Sprites/images/Snippet/Enemy/SaiRocket.png");
    EnemyImage[4] = myLoadGraph("Assets/Sprites/images/Snippet/Enemy/Titanian.png");
    LucasBattleImage = myLoadGraph("Assets/Sprites/images/Snippet/Lucas/LucasBattle.png");
    BoneyBattleImage = myLoadGraph("Assets/Sprites/images/Snippet/Boney/BoneyBattle.png");
    KumatoraBattleImage = myLoadGraph("Assets/Sprites/images/Snippet/Kumatora/KumatoraBattle.png");
    DusterBattleImage = myLoadGraph("Assets/Sprites/images/Snippet/Duster/DusterBattle.png");
    MessageWindow = myLoadGraph("Assets/Sprites/images/Snippet/Battle/Message.png");
    myLoadDivGraph("Assets/Sprites/images/Snippet/status.png", 80, 10, 8, 8, 8, drumroll);
    myLoadDivGraph("Assets/Sprites/images/Snippet/hiragana.png", 90, 10, 9, 7, 7, characterHiragana);
    myLoadDivGraph("Assets/Sprites/images/Snippet/katakana.png", 90, 10, 9, 7, 7, characterKatakana);
    myLoadDivGraph("Assets/Sprites/images/Snippet/alphaA.png", 90, 10, 9, 7, 7, characterAlphaA);
    myLoadDivGraph("Assets/Sprites/images/Snippet/Battle/Number.png", 30, 10, 3, 16, 16, battleCharacter);
    myLoadDivGraph("Assets/Sprites/images/Snippet/backgroundsA.png", 14, 4, 4, 256, 256, backgroundsA);

}


int SnippetImage::getCharacterBattleImage(int characterNumber) const {
    switch (characterNumber) {
    case 0:
        return LucasBattleImage;
    case 1:
        return KumatoraBattleImage;
    case 2:
        return DusterBattleImage;
    case 3:
        return BoneyBattleImage;
    }
    return LucasBattleImage;
}

/*!
@brief 今までロードした画像を解放する
*/
void SnippetImage::release()
{
    const int size = images.size();
    for (int i = 0; i < size; i++) {
        DeleteGraph(images[i]);
    }
    images.clear();
}


/*!
@brief LoadGraphをして、かつそのハンドルをメンバ変数に追加する
*/
int SnippetImage::myLoadGraph(char* fileName)
{
    int ret = LoadGraph(fileName);
    images.push_back(ret);
    return ret;
}

/*!
@brief LoadGraphをして、かつそのハンドルをメンバ変数に追加する
*/
int SnippetImage::myLoadGraph(const char* fileName)
{
    int ret = LoadGraph(fileName);
    images.push_back(ret);
    return ret;
}

/*!
@brief LoadDivGraphをして、かつそのハンドルをメンバ変数に追加する
*/
int SnippetImage::myLoadDivGraph(char* fileName, int n, int xn, int yn, int w, int h, int* buf)
{
    int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
    for (int i = 0; i < n; i++) {
        images.push_back(buf[i]);
    }
    return ret;
}

int SnippetImage::myLoadDivGraph(const char* fileName, int n, int xn, int yn, int w, int h, int* buf)
{
    int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
    for (int i = 0; i < n; i++) {
        images.push_back(buf[i]);
    }
    return ret;
}
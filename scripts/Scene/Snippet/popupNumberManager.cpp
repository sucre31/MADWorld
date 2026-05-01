#include "PopupNumberManager.h"
#include <DxLib.h>
#include "Common/Image.h"
#include "SnippetGameManager.h"

PopupNumberManager::PopupNumberManager(std::shared_ptr<SnippetGameManager> gameManager, std::shared_ptr<SnippetImage> Image) 
    : snippetGameManager(gameManager), snippetImage(Image){

}

PopupNumberManager::~PopupNumberManager() {
    for (auto n : numbers) {
        delete n;
    }
    numbers.clear();
}

bool PopupNumberManager::update() {
    double dt = snippetGameManager->getFpsIns()->getDeltaTime();

    for (int i = 0; i < numbers.size(); i++) {
        PopupNumber* n = numbers[i];

        // 寿命減少
        n->life -= dt;

        // 全体進行度（0 → 1）
        double t = 1.0 - (n->life / n->totalLife);
        if (t < 0.0) t = 0.0;
        if (t > 1.0) t = 1.0;

        if (t < 0.5) {
            // 前半：移動フェーズ（0 → 1 に正規化）
            double moveT = t / 0.5;

            // easeOut
            double ease = 1.0 - (1.0 - moveT) * (1.0 - moveT);

            n->y = n->startY + (n->targetY - n->startY) * ease;
        }
        else {
            // 後半：停止
            n->y = n->targetY;
        }

        // 消える
        if (n->life <= 0.0) {
            delete n;
            numbers.erase(numbers.begin() + i);
            i--;
        }
    }

    return true;
}


void PopupNumberManager::draw() const {
    for (auto n : numbers) {
        int value = n->value;

        if (value < 10) {
            DrawGraph((int)n->x, (int)n->y,
                snippetImage->getBattleCharacter()[value], TRUE);
        }
        else if (value < 100) {
            DrawGraph((int)n->x - 9, (int)n->y,
                snippetImage->getBattleCharacter()[(value / 10) % 10], TRUE);
            DrawGraph((int)n->x, (int)n->y,
                snippetImage->getBattleCharacter()[value % 10], TRUE);
        }
        else {
            DrawGraph((int)n->x - 18, (int)n->y,
                snippetImage->getBattleCharacter()[(value / 100) % 10], TRUE);
            DrawGraph((int)n->x - 9, (int)n->y,
                snippetImage->getBattleCharacter()[(value / 10) % 10], TRUE);
            DrawGraph((int)n->x, (int)n->y,
                snippetImage->getBattleCharacter()[value % 10], TRUE);
        }
    }
}

void PopupNumberManager::add(int value, int x, int y) {
    PopupNumber* n = new PopupNumber();

    if (value < 0) value = 0;

    n->value = value;
    n->x = x;

    n->targetY = y;        // 最終位置
    n->startY = y + 10;    // 下からスタート（調整ポイント）
    n->y = n->startY;

    n->life = 1.0;         // 1秒
    n->totalLife = 1.0;

    numbers.push_back(n);
}
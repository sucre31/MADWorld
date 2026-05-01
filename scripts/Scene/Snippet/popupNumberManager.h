#pragma once
#include <vector>
#include "SnippetGameManager.h"
#include "SnippetImage.h"

struct PopupNumber {
    int value;
    double x;

    double startY;
    double targetY;
    double y;

    double life;
    double totalLife;
};

class PopupNumberManager {
public:
    PopupNumberManager(std::shared_ptr<SnippetGameManager> snippetGameManager, std::shared_ptr<SnippetImage> snippetImage);
    ~PopupNumberManager();

    bool update();
    void draw() const;

    void add(int value, int x, int y);

private:
    std::vector<PopupNumber*> numbers;
    std::shared_ptr<SnippetGameManager> snippetGameManager;
    std::shared_ptr<SnippetImage> snippetImage;
};
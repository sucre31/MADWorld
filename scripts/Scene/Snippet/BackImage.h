#pragma once
#include <memory>
#include "GameObject.h"
#include "SnippetImage.h"
#include "SnippetGameManager.h"

class BackImage : public GameObject
{
public:
	BackImage();
	~BackImage() = default;
	bool update() override;
	void draw() const override;
	void drawSecond() const;
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	int AnimeNum;
	int deley;
	int tmpScreenHandle;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetImage> snippetImage;
};


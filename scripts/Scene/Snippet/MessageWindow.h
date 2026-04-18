#pragma once
#include <memory>
#include "Common/GameObject/GameObject.h"
#include "SnippetGameManager.h"
#include "SnippetImage.h"
//#include "StringImage.h"

class MessageWindow : GameObject
{
public:
	MessageWindow(std::shared_ptr<SnippetGameManager> managerIns, std::shared_ptr<SnippetImage> image);
	~MessageWindow() = default;
	bool update() override;
	void draw() const override;
	void setMessage(int ID);
	void SetGameManager(std::shared_ptr<SnippetGameManager> ins) { snippetGameManager = ins; }
	void SetImage(std::shared_ptr<SnippetImage> ins) { snippetImage = ins; }
private:
	//std::string strBattleMessage[4];
	//std::shared_ptr<StringImage> stringImage;
	int currentTurn;
	int messageCounter;
	int myX, myY;
	int currentMessageID;
	bool messageFlag;
	std::shared_ptr<SnippetGameManager> snippetGameManager;
	std::shared_ptr<SnippetImage> snippetImage;
};


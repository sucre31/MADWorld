#pragma once
#include "GameObject.h"
#include "Pad.h"

class Sozai : public GameObject
{
public:
	Sozai();
	~Sozai() {};
	void setMyId(int id) { myId = id; }
	bool update() override;
	void draw() const override;
	void setPosX(int xVal) { x = xVal; }
	void setPosY(int yVal) { y = yVal; }
	void setSampleMovie(const char* fileName);
	void setSampleSound(const char * fileName);
	void playSample();
	void setTriggerButton(int padEnum) { triggerButton = padEnum; }
	int getTriggerButton() { return (int)triggerButton; };
private:
	int myId;	// managerƒNƒ‰ƒX‚ÌŠÇ—”Ô†
	int x;
	int y;
	int myGrapghHandle;
	int mySoundHandle;
	bool enableTurn;
	bool turnFlag;
	int triggerButton;
};


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
	void setExRate(double val) { exRate = val; }
	void setSampleMovie(const char* fileName);
	void setSampleSound(const char * fileName);
	void playSample();
	void setTriggerButton(int padEnum) { triggerButton = padEnum; }
	int getTriggerButton() { return (int)triggerButton; };
private:
	int myId;	// managerクラスの管理番号
	int x;
	int y;
	int myGrapghHandle;
	int mySoundHandle;
	double exRate;
	bool enableTurn;
	bool turnFlag;
	int triggerButton;
};


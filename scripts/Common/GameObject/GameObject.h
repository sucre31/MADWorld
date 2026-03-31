#pragma once
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	virtual bool update() = 0;
	virtual void draw() const = 0;
	double getPosX() { return posX; }
	double getPosY() { return posY; }
	void setPosX(double val) { posX = val; }
	void setPosY(double val) { posY = val; }
protected:
	double posX;
	double posY;
};
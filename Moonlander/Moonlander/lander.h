#ifndef LANDER_H
#define LANDER_H

#include "point.h"
#include "velocity.h"


class Lander
{
private:
	bool alive;
	bool landed;
	int fuel;
	Point pos;
	Velocity vel;

public:
	// lander default constructor
	Lander();
	~Lander();

	//getters
	Point getPoint()       const { return pos; };
	Velocity getVelocity() const { return vel; };
	int getFuel()          const { return fuel; };

	//check status
	bool isAlive()         const { return alive; };
	bool isLanded()        const { return landed; };
	bool canThrust()       const { return fuel != 0 && !isLanded() && isAlive(); };

	//setters
	void setLanded(bool b);
	void setAlive(bool b);
	void setFuel(int i);

	// apply direction
	void applyGravity(double x);
	void applyThrustLeft();
	void applyThrustRight();
	void applyThrustBottom();

	//callbacks
	void advance();
	void draw();
	void reset();
};
#endif



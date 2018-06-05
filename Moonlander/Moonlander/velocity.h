#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float dx;
	float dy;

public:
	//constructor
	Velocity();
	//non default constructor
	Velocity(float dx, float dy);
	~Velocity();

	// getters
	float getDx() const { return dx; };
	float getDy() const { return dy; };

	// setters
	void setDx(float Dx);
	void setDy(float Dy);


};
#endif


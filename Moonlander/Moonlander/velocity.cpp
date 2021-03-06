#include "velocity.h"


/************************************************************************
* velocity default constructor
*************************************************************************/
Velocity::Velocity()
{
}

/************************************************************************
* non-default constructors
*************************************************************************/
Velocity::Velocity(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

/************************************************************************
* destructors
*************************************************************************/
Velocity::~Velocity()
{
}

/************************************************************************
* set direction on x axis
*************************************************************************/
void Velocity::setDx(float Dx)
{
	dx = Dx;
}

/************************************************************************
* set dircection on y axis
*************************************************************************/
void Velocity::setDy(float Dy)
{
	dy = Dy;
}

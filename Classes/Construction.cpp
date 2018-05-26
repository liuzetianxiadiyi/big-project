#include "Construction.h"

void Construction::sethp(int damage)
{
	health_point -= damage;
}

void  Construction::setDestroy()
{
	destroy = true;
}

void  Construction::setSelected(bool b)
{
	Selected = b;
}

Vec2 Construction::getLocation()
{
	return location;
}
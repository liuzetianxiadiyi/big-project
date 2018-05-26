#include "Military.h"

void Military::init(string _name, int _health_point, int _power, int _speed, int _delay,bool _dead,bool _Selected,Vec2 _position,Vec2 _destination)
{
	name = _name;
	health_point = _health_point;
	power = _power;
	speed = _speed;
	delay = _delay;
	dead = _dead;
	Selected = _Selected;
	position = _position;
	destination = _destination;
}

void Military::sethp(int damage)
{
	health_point -= damage;
}

void Military::setDestination(Vec2 v)
{
	destination = v;
}

void Military::setdead()
{
	dead = true;
}

void Military::setSelected(bool b)
{
	Selected = b;
}

void Military::attack(Military* sprite)
{
	sprite->sethp(power);
}
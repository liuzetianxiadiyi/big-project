#include "Military.h"

Military* Military::create(string& filename)
{
	Military* sprite = new Military();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->create = Sprite::create("filename");

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

void Military::init(int _health_point, bool _dead, bool _Selected, Vec2 _position, float _destinationX,float _destinationY, Action* _move)
{
	name = _name;
	health_point = _health_point;
	dead = _dead;
	Selected = _Selected;
	position = _position;
	destinationX = _destinationX;
	destinationY = _destinationY;
	move = _move;
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

int Military::gethp()const
{
	return health_point;
}

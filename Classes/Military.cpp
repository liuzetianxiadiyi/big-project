#include "Military.h"
#include"soldiers.h"

void Military::init(int _health_point, bool _dead, bool _Selected, Vec2 _position, Vec2 _destination)
{
	health_point = _health_point;
	max_hp= _health_point;
	dead = _dead;
	Selected = _Selected;
	position = _position;
	destination = _destination;
}

void Military::setPosition(Vec2 vec)
{
	position = vec;
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

void Military::createBar(Military * a)
{
	Sprite *hpSprite = Sprite::create("hp.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);
	hp->setMidpoint(Point(0, 0));
	hp->setBarChangeRate(Point(1, 0));
	hp->setPosition(Vec2(32, 67));
	hp->setPercentage(100);
}
void Military::attack(Military* sprite)
{
	int pTemp;
	if (typeid(*this) == typeid(Soldier))
		pTemp = Soldier::power;
	else if (typeid(*this) == typeid(Dog))
		pTemp = Dog::power;
	else if (typeid(*this) == typeid(Engineer))
		pTemp = Engineer::power;
	sprite->sethp(pTemp);

}

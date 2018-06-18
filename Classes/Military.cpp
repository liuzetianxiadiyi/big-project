#include "Military.h"
#include "Soldier.h"
Military* Military::create(string& filename)
{
	Military* sprite = new Military();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

void Military::init(int _health_point, bool _dead, bool _Selected, Vec2 _position, float _destinationX,float _destinationY, Action* _move)
{
	name = _name;
	health_point = _health_point;
	max_hp= _health_point;
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
	position = v;
}

void Military::setdead()
{
	dead = true;
}

void Military::setSelected(bool b)
{
	Selected = b;
}

void Military::createBar(Sprite * a)
{
	Sprite *hpSprite = Sprite::create("hp.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);//条形
	hp->setMidpoint(Point(0, 0));//血条起始点
	hp->setBarChangeRate(Point(1, 0));//血条改变的是x方向
	hp->setPosition(Vec2(32, 67));//血条相对精灵的位置
	hp->setPercentage((health_point / max_hp) * 100);//设置值
	a->addChild(hp, 1);//把血条绑定在精灵上
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

int Military::gethp()
{
	return health_point;
}


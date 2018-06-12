#include "Military.h"

Military* Military::create(string& filename)
{
	Military* sprite = new Military();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->create = Sprite::create("filename");
		Sprite *hpSprite = Sprite::create("hp.png");
		
		Sprite *bgSprite = Sprite::create("hpk.png");
		bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		sprite->addChild(bgSprite, 1, 1);

		auto progressTimer = ProgressTimer::create(hpSprite);
		progressTimer->setType(ProgressTimer::Type::BAR);//条形
		progressTimer->setMidpoint(Point(0, 0));//血条起始点
		progressTimer->setBarChangeRate(Point(1, 0));//血条改变的是x方向
		progressTimer->setPosition(Vec2(32, 67));//血条相对精灵的位置
		progressTimer->setPercentage(100);//设置值

		sprite->addChild(progressTimer, 1, 1);//把血条绑定在精灵上


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

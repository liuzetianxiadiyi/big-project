#include "Soldiers.h"

int Soldier::money = 500;
int Dog::money = 300;
int Engineer::money = 800;
int Engineer::cure = 10;

Soldier* Soldier::create(string & filename)
{
	Soldier* sprite = new Soldier();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->create = Sprite::create("filename");
		sprite->init("Soldier", 200, 30, 10, 0.5f, false, false, Vec2(300, 300), Vec2(0, 0), Vec2(300, 310));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

Dog* Dog::create(string & filename)
{
	Dog* sprite = new Dog();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->create = Sprite::create("filename");
		sprite->init("Dog", 100, 50, 30, 0.5f, false, false, Vec2(300, 300), Vec2(0, 0),Vec2(300, 310));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}


Engineer* Engineer::create(string & filename)
{
	Engineer* sprite = new Engineer();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->create = Sprite::create("filename");
		sprite->init("Engineer", 350, 0, 15, 0.5f, false, false, Vec2(300, 300), Vec2(300, 300));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

/*
Sprite *hpSprite = Sprite::create("hp.png");
auto hp = ProgressTimer::create(hpSprite);
hp->setType(ProgressTimer::Type::BAR);//条形
hp->setMidpoint(Point(0, 0));//血条起始点
hp->setBarChangeRate(Point(1, 0));//血条改变的是x方向
hp->setPosition(Vec2(32, 67));//血条相对精灵的位置
hp->setPercentage(100);//设置值

pSprite->addChild(hp, 1, 1);//把血条绑定在精灵上
*/


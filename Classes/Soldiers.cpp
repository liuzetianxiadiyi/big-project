#include "Soldiers.h"

int Soldier::money = 500;
int Dog::money = 300;
int Engineer::money = 800;
int Engineer::cure = 10;

Soldier* Soldier::create(const string  filename)
{
	Soldier* sprite = new Soldier();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();


		sprite->init( 200,false,false, Vec2(300, 300),Vec2(0,0), MoveBy::create(sprite->getSpeed(), sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

Dog* Dog::create(const string filename)
{
	Dog* sprite = new Dog();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->init( 100, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(sprite->getSpeed(),sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}


Engineer* Engineer::create(const string filename)
{
	Engineer* sprite = new Engineer();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->init( 350,  false, false, Vec2(300, 300), Vec2(300, 300), MoveBy::create(sprite->getSpeed(),sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

Tank* Tank::create(const string filename)
{
	Tank* sprite = new Tank();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->init(500, false, false, Vec2(300, 300), Vec2(300, 300), MoveBy::create(sprite->getSpeed(), sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

Miningcar* Miningcar::create(const string filename)
{
	Miningcar* sprite = new Miningcar();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->init(500, false, false, Vec2(300, 300), Vec2(300, 300), MoveBy::create(sprite->getSpeed(), sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};



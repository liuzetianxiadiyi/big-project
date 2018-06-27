#include "Soldiers.h"

int Soldier::money = 500;
int Dog::money = 300;
int Engineer::money = 800;
int Tank::money = 1000;
//int Miningcar::money = 100;

int Soldier::speed = 10;
int Dog::speed = 15;
int Engineer::speed = 10;
int Tank::speed = 20;
int Miningcar::speed = 20;

int Soldier::delay = 5;
int Dog::delay = 8;
int Engineer::delay = 10;
int Tank::delay = 15;
int Miningcar::delay = 20;

int Soldier::power = 15;
int Dog::power = 15;
int Engineer::power = 0;
int Tank::power = 30;
int Miningcar::money = 0;

int Engineer::cure = 10;

Soldier* Soldier::create(const string  filename)
{
	Soldier* sprite = new Soldier();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->init( 200,false,false, Vec2(300, 300),Vec2(0,0));
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

		sprite->init( 350,  false, false, Vec2(300, 300), Vec2(300, 300));
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

		sprite->init(500, false, false, Vec2(300, 300), Vec2(300, 300));
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

		sprite->init(500, false, false, Vec2(300, 300), Vec2(300, 300));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};



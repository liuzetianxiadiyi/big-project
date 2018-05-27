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
		sprite->init("Soldier", 200, 30, 10, 0.5f, false, false, Vec2(300, 300), Vec2(0, 0));

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
		sprite->init("Dog", 100, 50, 30, 0.5f, false, false, Vec2(300, 300), Vec2(0, 0));

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

Engineer* Engineer::create(string & filename)
{
	Engineer* sprite = new Engineer();

	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();

		sprite->create = Sprite::create("filename");
		sprite->init("Engineer", 350, 0, 15, 0.5f, false, false, Vec2(300, 300), Vec2(300, 300));

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};


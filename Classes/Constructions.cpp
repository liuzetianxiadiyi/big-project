#include "Constructions.h"



int Mine::money = 1000;

int Barracks::money = 2000;

int Warfactory::money = 3000;

int Base::money = 5000;





Barracks* Barracks::create(string & filename)

{

	Barracks* sprite = new Barracks();



	if (sprite->initWithFile(filename))

	{

		//待优化

		sprite->autorelease();

		sprite->createdog = Sprite::create("filename");

		sprite->createsolder = Sprite::create("filename");

		sprite->createengineer = Sprite::create("filename");



		sprite->init("Barracks", 1000, 4, Vec2(300, 300), false, false, 1, 100);



		return sprite;

	}



	CC_SAFE_DELETE(sprite);

	return nullptr;

}



Warfactory* Warfactory::create(string & filename)

{

	Warfactory* sprite = new Warfactory();



	if (sprite->initWithFile(filename))

	{

		//待优化

		sprite->autorelease();

		sprite->createtank = Sprite::create("filename");



		sprite->init("Warfactory", 1800, 4, Vec2(400, 400), false, false, 1, 100);



		return sprite;

	}



	CC_SAFE_DELETE(sprite);

	return nullptr;

}



Mine* Mine::create(string & filename)

{

	Mine* sprite = new Mine();



	if (sprite->initWithFile(filename))

	{

		//待优化

		sprite->autorelease();

		sprite->createminingcar = Sprite::create("filename");



		sprite->init("Mine", 1600, 4, Vec2(150, 150), false, false, 1, 100);



		return sprite;

	}



	CC_SAFE_DELETE(sprite);

	return nullptr;

}



Base* Base::create(string & filename)

{

	Base* sprite = new Base();



	if (sprite->initWithFile(filename))

	{

		//待优化

		sprite->autorelease();

		sprite->createbarracks = Sprite::create("filename");

		sprite->createwarfactory = Sprite::create("filename");

		sprite->createmine = Sprite::create("filename");



		sprite->init("Base", 5000, 8, Vec2(100, 100), false, false, 1, 100);



		return sprite;

	}



	CC_SAFE_DELETE(sprite);

	return nullptr;

}

void CreateDogCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Dog::delay);
	auto seq = Sequence::create(delay, CreateDog,nullptr);
}

void CreateSoldierCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Soldier::delay);
	auto seq = Sequence::create(delay, CreateDog, nullptr);
}

void CreateEngineerCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Engineer::delay);
	auto seq = Sequence::create(delay, CreateDog, nullptr);
}


//代码重用
void CreateDog()
{
	string filename = "filename";
	Dog* dog = Dog::create(filename);
	dog->init("Dog", 100, 50, 30, 0.5f, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(dog->getSpeed(), dog->getDestination()), 300);
	dog->setPosition();
	this->addChild(dog, 2);
}

void CreateSoldier()
{
	string filename = "filename";
	Soldier* soldier = Solider::create(filename);
	soldier->init();
	soldier->setPosition();
	this->addChild(soldier, 2);
}

void CreateEngineer()
{
	string filename = "filename";
	Engineer* engineer = Engineer::create(filename);
	engineer->init();
	engineer->setPosition();
	this->addChild(engineer, 2);
}
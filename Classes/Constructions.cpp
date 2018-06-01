#include "Constructions.h"
#include "Soldiers.h"

int Barracks::money = 2000;

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

		sprite->init("Barracks", 1000, 4, Vec2(300, 300), false, false, 1,100);

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
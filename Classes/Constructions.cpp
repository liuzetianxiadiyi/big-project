#include "Constructions.h"
#include "Soldiers.h"

int Mine::money = 1000;
int Barracks::money = 2000;
int Warfactory::money = 3000;
int Base::money = 5000;

Barracks* Barracks::create(const string filename)
{
	Barracks* sprite = new Barracks();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createdog = Sprite::create("filename");
		sprite->createsoldier = Sprite::create("filename");
		sprite->createengineer = Sprite::create("filename");
		sprite->init("Barracks", 1000, 4, Vec2(300, 300), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Warfactory* Warfactory::create(const string filename)
{
	Warfactory* sprite = new Warfactory();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createtank = Sprite::create("filename");
		sprite->init("Warfactory", 1800, 4, Vec2(400, 400), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Mine* Mine::create(const string filename)
{
	Mine* sprite = new Mine();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createminingcar = Sprite::create("filename");
		sprite->init("Mine", 1600, 4, Vec2(150, 150), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Base* Base::create(const string filename)
{
	Base* sprite = new Base();
	if (sprite->initWithFile(filename))
	{
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

void Barracks::CreateDogCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Dog::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateSoldierCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Soldier::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateEngineerCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Engineer::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateDog()
{
	string filename = "filename";
	Dog* dog = Dog::create(filename);
	dog->init(100,  false, false, Vec2(300, 300),Vec2(0,0),MoveBy::create(dog->getSpeed(), dog->getDestination()));
	dog->setPosition(Vec2(0,0));
	auto target=  Director::getInstance()->getRunningScene();
	target->addChild(dog, 2); 
}

void Barracks::CreateSoldier()
{
	string filename = "filename";
	Soldier* soldier = Soldier::create(filename);
	soldier->init(200, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(soldier->getSpeed(), soldier->getDestination()));
	soldier->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	target->addChild(soldier, 2);
}

void Barracks::CreateEngineer()
{
	string filename = "filename";
	Engineer* engineer = Engineer::create(filename);
	engineer->init(200, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(engineer->getSpeed(), engineer->getDestination()));
	engineer->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	target->addChild(engineer, 2);
}

void Warfactory::CreateTank()
{
	string filename = "filename";
	Tank* tank = Tank::create(filename);
	tank->init(200, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(tank->getSpeed(), tank->getDestination()));
	tank->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	target->addChild(tank, 2);
}

void Warfactory::CreateTankCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Tank::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateTank(); }, nullptr);
	this->runAction(seq);
}

void Mine::CreateMiningcar()
{
	string filename = "filename";
	Miningcar* miningcar = Miningcar::create(filename);
	miningcar->init(200, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(miningcar->getSpeed(), miningcar->getDestination()));
	miningcar->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	target->addChild(miningcar, 2);
}

void Mine::CreateMiningcarCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Miningcar::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateMiningcar(); }, nullptr);
	this->runAction(seq);
}

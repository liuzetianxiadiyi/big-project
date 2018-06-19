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


		sprite->init( 200,false,false, Vec2(300, 300),Vec2(0,0), MoveBy::create(sprite->getSpeed(), sprite->getDestination()));
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

		sprite->init( 100, false, false, Vec2(300, 300), Vec2(0, 0), MoveBy::create(sprite->getSpeed(),sprite->getDestination()));
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

		sprite->init( 350,  false, false, Vec2(300, 300), Vec2(300, 300), MoveBy::create(sprite->getSpeed(),sprite->getDestination()));
		createBar(sprite);
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
};

/*
Sprite *hpSprite = Sprite::create("hp.png");
auto hp = ProgressTimer::create(hpSprite);
hp->setType(ProgressTimer::Type::BAR);//鏉″舰
hp->setMidpoint(Point(0, 0));//琛€鏉¤捣濮嬬偣
hp->setBarChangeRate(Point(1, 0));//琛€鏉℃敼鍙樼殑鏄痻鏂瑰悜
hp->setPosition(Vec2(32, 67));//琛€鏉＄浉瀵圭簿鐏电殑浣嶇疆
hp->setPercentage(100);//璁剧疆鍊?

pSprite->addChild(hp, 1, 1);//鎶婅鏉＄粦瀹氬湪绮剧伒涓?
*/


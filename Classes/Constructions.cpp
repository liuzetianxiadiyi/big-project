#include "Constructions.h"

int Barracks::money = 2000;

Barracks* Barracks::create(string & filename)
{
	Barracks* sprite = new Barracks();
	
	if (sprite->initWithFile(filename))
	{
		//´ýÓÅ»¯
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
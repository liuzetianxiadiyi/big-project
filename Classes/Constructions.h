#ifndef __CONSTRUCTIONS_H__
#define __CONSTRUCTIONS_H__

#include "Construction.h"

class Barracks:public Construction
{
private:
	//use to create menu
	Sprite * createdog;
	Sprite * createsoldier;
	Sprite * createengineer;

public:
	static Barracks* create(string & filename);
	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	void CreateDogCallback(Ref* pSender);
	void CreateSoldierCallback(Ref* pSender);
	void CreateEngineerCallback(Ref* pSender);

	void CreateDog();
	void CreateSoldier();
	void CreateEngineer();

	virtual Menu* createMenu()
	{
		auto dogItem = MenuItemSprite::create(createdog, createdog, CC_CALLBACK_1(Barracks::CreateDogCallback, this));
		auto soldierItem = MenuItemSprite::create(createsoldier, createsoldier, CC_CALLBACK_1(Barracks::CreateSoldierCallback, this));
		auto engineerItem = MenuItemSprite::create(createengineer, createengineer, CC_CALLBACK_1(Barracks::CreateEngineerCallback, this));
	}
	static int money;
	virtual void None() {};

	Sprite* getdog()
	{
		return createdog;
	}

	Sprite* getsolder()
	{
		return createsoldier;
	}

	Sprite* getengineer()
	{
		return createengineer;
	}
};

class Warfactory :public Construction
{
public:

	//button
	Sprite * createtank;

public:

	static Warfactory* create(string & filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//*******************
	void CreateTankCallback(Ref* pSender);
	void CreateTank();
	virtual Menu* createMenu();
	//*******************

	static int money;
	virtual void None() {};

	Sprite* gettank()
	{

		return createtank;

	}
};

class Mine :public Construction
{

public:

	//button
	Sprite * createminingcar;
public:

	static Mine* create(string & filename);
	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//*******************
	void CreateMiningcarCallback(Ref* pSender);
	void CreateMiningcar();
	virtual Menu* createMenu();
	//*******************

	static int money;
	virtual void None() {};
	Sprite* getminingcar()
	{
		return createminingcar;
	}
};

class Base :public Construction
{

public:
	//button
	Sprite * createbarracks;

	Sprite * createwarfactory;

	Sprite * createmine;

public:

	static Base* create(const string & filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	static int money;

	virtual void None() {};
	Sprite* getbarracks()
	{
		return createbarracks;
	}

	Sprite* getwarfactory()
	{
		return createwarfactory;
	}

	Sprite* getmine()
	{
		return createmine;
	}
};

#endif

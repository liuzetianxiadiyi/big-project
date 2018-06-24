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
	static Barracks* create(const string filename);
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

	static void createBar(Barracks * a);

	virtual Menu* createMenu()
	{
		auto dogItem = MenuItemSprite::create(createdog, createdog, CC_CALLBACK_1(Barracks::CreateDogCallback, this));
		auto soldierItem = MenuItemSprite::create(createsoldier, createsoldier, CC_CALLBACK_1(Barracks::CreateSoldierCallback, this));
		auto engineerItem = MenuItemSprite::create(createengineer, createengineer, CC_CALLBACK_1(Barracks::CreateEngineerCallback, this));
	}

	virtual void None() {};

	Sprite* getdog();

	Sprite* getsolder();

	Sprite* getengineer();
};

class Warfactory :public Construction
{
public:

	//button
	Sprite * createtank;

public:

	static Warfactory* create(const string filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//*******************
	void CreateTankCallback(Ref* pSender);
	void CreateTank();

	static void createBar(Warfactory * a);

	virtual Menu* createMenu() {
		auto tankItem = MenuItemSprite::create(createtank, createtank, CC_CALLBACK_1(Warfactory::CreateTankCallback, this));
	}

	virtual void None() {};

	Sprite* gettank();
};

class Mine :public Construction
{

public:

	//button
	Sprite * createminingcar;
public:

	static Mine* create(const string filename);
	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//*******************
	void CreateMiningcarCallback(Ref* pSender);
	void CreateMiningcar();

	static void createBar(Mine * a);

	virtual Menu* createMenu() {
		auto miningcarItem = MenuItemSprite::create(createminingcar, createminingcar, CC_CALLBACK_1(Mine::CreateMiningcarCallback, this));
	}

	virtual void None() {};
	Sprite* getminingcar();
};

class Base :public Construction
{

public:
	//button
	Sprite * createbarracks;

	Sprite * createwarfactory;

	Sprite * createmine;

public:

	static Base* create(const string filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	static void createBar(Base * a);

	virtual void None() {};
	Sprite* getbarracks();

	Sprite* getwarfactory();

	Sprite* getmine();
};



#endif

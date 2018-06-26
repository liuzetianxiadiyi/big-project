#ifndef __CONSTRUCTIONS_H__
#define __CONSTRUCTIONS_H__
#include "Construction.h"

class Barracks:public Construction
{
private:

public:

	//use to create menu
	Sprite * createdog;
	Sprite * createsoldier;
	Sprite * createengineer;

	static int money;
	static float delay;
	static int max_hp;
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

	void createBar(Barracks * a);

	virtual Menu* createMenu();

	virtual void None() {};

	Sprite* getdog();
	Sprite* getsolder();
	Sprite* getengineer();

};

class Warfactory :public Construction
{
public:
	static int money;
	static float delay;
	static int max_hp;
	
public:
	//button
	Sprite * createtank;
	static Warfactory* create(const string filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	void CreateTankCallback(Ref* pSender);
	void CreateTank();

	void createBar(Warfactory * a);

	virtual Menu* createMenu() 
	{
		auto tankItem = MenuItemSprite::create(createtank, createtank, CC_CALLBACK_1(Warfactory::CreateTankCallback, this));
		auto menu = Menu::create(tankItem, NULL);
		return menu;
	}

	virtual void None() {};

	Sprite* gettank();
};

class Mine :public Construction
{

public:
	static int money;
	static float delay;
	static int max_hp;
	//button
	Sprite * createminingcar;
public:

	static Mine* create(const string filename);
	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	void CreateMiningcarCallback(Ref* pSender);
	void CreateMiningcar();

	void createBar(Mine * a);

	virtual Menu* createMenu();

	virtual void None() {};
	Sprite* getminingcar();
};

class Base :public Construction
{

public:
	static int money;
	static float delay;
	static int max_hp;
	//button
	Sprite * createbarracks;// = Sprite::create("Barracks.png");
	Sprite * createwarfactory;// = Sprite::create("Warfactory.png");
	Sprite * createmine;// = Sprite::create("Mine.png");

public:

	static Base* create(const string filename);

	/*static Barracks* create(const std::string & filename, const Rect & rect);
	static Barracks* createWithTexture(Texture2D * texture);
	static Barracks* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Barracks* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Barracks* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	void createBar(Base * a);

	virtual void None() {};

	virtual Menu* createMenu();
	

	void CreateMineCallback(Ref* pSender);
	void CreateWarfactoryCallback(Ref* pSender);
	void CreateBarracksCallback(Ref* pSender);

	void CreateMine();
	void CreateBarracks();
	void CreateWarfactory();

	Sprite* getbarracks();
	Sprite* getwarfactory();
	Sprite* getmine();
};

#endif

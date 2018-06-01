#ifndef __CONSTRUCTIONS_H__
#define __CONSTRUCTIONS_H__

#include "Construction.h"

class Barracks:public Construction
{
public:
	//use to create menu
	Sprite * createdog;
	Sprite * createsolder;
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

	static int money;

	virtual void None() {};

	Sprite* getdog()
	{
		return createdog;
	}

	Sprite* getsolder()
	{
		return createsolder;
	}

	Sprite* getengineer()
	{
		return createengineer;
	}
};

#endif

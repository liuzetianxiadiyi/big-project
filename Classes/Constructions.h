#ifndef __CONSTRUCTIONS_H__

#define __CONSTRUCTIONS_H__



#include "Construction.h"



class Barracks :public Construction

{

public:

	//button

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

	static Base* create(string & filename);

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
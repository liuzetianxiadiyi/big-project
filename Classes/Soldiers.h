#ifndef __SOLDIERS_H__
#define __SOLDIERS_H__
#include"Military.h"
#include"Construction.h"

USING_NS_CC;
using std::string;


class Soldier : public Military
{
	
public:
	Sprite * create;
	static Soldier* create(string & filename);
	
	/*static Soldier* create(const std::string & filename, const Rect & rect);
	static Soldier* createWithTexture(Texture2D * texture);
	static Soldier* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Soldiers* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Soldier* createWithSpriteFrameName(const std::string & spriteFrameName);*/
	
	static int money;

	virtual void None() {};
	
	Sprite* create()
	{
		return create;
	}
};

class Dog : public Military
{

public:
	Sprite * create;
	static Dog* create(string & filename);

	/*static Dog* create(const std::string & filename, const Rect & rect);
	static Dog* createWithTexture(Texture2D * texture);
	static Dog* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Dog* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Dog* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	static int money;

	virtual void None() {};

	Sprite* create()
	{
		return create;
	}

};

class Engineer : public Military
{

public:
	Sprite * create;

	void therapy(int cure)
	{
		int i = getPoint();
			 i+= cure;
	};
	
	static Engineer* create(string & filename);

	/*static Engineer* create(const std::string & filename, const Rect & rect);
	static Engineer* createWithTexture(Texture2D * texture);
	static Engineer* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Engineer* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Engineer* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	static int money;

	virtual void None() {};

	Sprite* create()
	{
		return create;
	}
	
private:
	
	static int cure;

};
#endif
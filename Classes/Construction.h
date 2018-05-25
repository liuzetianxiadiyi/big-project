#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "cocos2d.h"
#include <iostream>

using std::string;
USING_NS_CC;

class Construction:public cocos2d::Sprite
{
private:
	string name;
	int health_point;
	int view;
	Vec2 location;
	bool destroy;
	bool Selected;
	int sLevel;
	int delay;

public:
	void sethp(int damage)
	{
		health_point -= damage;
	}

	void setDestroy()
	{
		destroy = false;
	}

	void setSelected(bool b)
	{
		Selected = b;
	}

	Vec2 getLocation()
	{
		return location;
	}

	void setsLevel(int i)
	{
		sLevel = i;
	}

	virtual void None() = 0;

	static int money;

	static Construction* create(string & filename);
	static Construction* create(const std::string & filename, const Rect & rect);
	static Construction* createWithTexture(Texture2D * texture);
	static Construction* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Construction* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Construction* createWithSpriteFrameName(const std::string & spriteFrameName);

	void init(string _name, int _health_point, int _view,Vec2 _location,bool _destroy,bool _Selected,int _sLevel,int _delay)
	{
		name = _name;
		health_point = _health_point;
		view = _view;
		location = _location;
		destroy = _destroy;
		Selected = _Selected;
		sLevel = _sLevel;
		delay = _delay;
	}
};

#endif // !__CONSTRUCTION_H__

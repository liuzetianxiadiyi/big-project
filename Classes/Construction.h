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
	float delay;
	int country;

public:
	virtual Rect getBoundingBox()
	{
		Rect m_box = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
		return RectApplyAffineTransform(m_box, this->getNodeToWorldAffineTransform());
	}
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

	int gethp()
	{
		return health_point;
	}

	int getCountry()
	{
		return country;
	}

	virtual void None() = 0;

	static int money;
	virtual Menu* createMenu()=0;

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

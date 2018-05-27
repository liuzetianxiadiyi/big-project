#ifndef __MILITARY_H__
#define __MILITARY_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using std::string;

class Military : public Sprite
{
private:
	string name;
	int health_point;
	int power;
	int speed;
	int delay;
	Vec2 position;
	bool dead;
	Vec2 destination;
	bool Selected;

	//ValueVector data;

public:
	void attack(Military*);
	void sethp(int damage);
	void setDestination(Vec2 v);
	void setdead();
	void setSelected(bool b);
	int getPoint()const;

	void init(string _name, int _health_point, int _power, int _speed, int _delay, bool _dead, bool _Selected, Vec2 _position, Vec2 _destination);
	/*static Military* create(string & filename);
	static Military* create(const std::string & filename, const Rect & rect);
	static Military* createWithTexture(Texture2D * texture);
	static Military* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Military* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Military* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//virtual ValueVector& getValueVector() = 0;
};

#endif

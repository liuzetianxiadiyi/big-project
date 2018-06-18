#ifndef __FINDWAY_H__
#define __FINDWAY_H__

#include <iostream>
#include <vector>
#include<string>
#include "cocos2d.h"

USING_NS_CC;

#define TILENUMS 10
#define CHECKNUMS 8
#define WEIGHT 1000

using std::vector;
using std::pair;
using std::make_pair;
using std::string;


class Position
{
public:
	static pair<Vec2, Vec2> GetLocation(Vec2 point);
	static Vec2 GetTopright(Vec2 tpoint);
	static Vec2 GetTopleft(Vec2 tpoint);
	static Vec2 GetBelowright(Vec2 tpoint);
	static Vec2 GetBelowleft(Vec2 tpoint);
};

class MyTile :public cocos2d::Ref
{
private:
	int f_value;
	int h_value;
	int g_value;
	MyTile* parent;
	Vec2 pos;
	Vec2 goal;
public:
	static MyTile* create(MyTile* _parent, Vec2 _pos, Vec2 _goal)
	{
		MyTile* tile = new MyTile();
		tile->init(_parent, _pos, _goal);
		tile->autorelease();
		return tile;
	}
	void set_hv()
	{
		int temp_x = goal.x - pos.x;
		int temp_y = goal.y - pos.y;
		h_value += (abs(temp_x) + abs(temp_y));
	}
	Vec2 GetPosition()
	{
		return pos;
	}
	int Get_gv()
	{
		return g_value;
	}

	void changeValue(int count)
	{
		f_value -= count;
	}

	void init(MyTile* _parent, Vec2 _pos, Vec2 _goal)
	{
		parent = _parent;
		pos = _pos;
		goal = _goal;
		set_hv();
		if (parent != NULL)
		{
			g_value = parent->Get_gv() + 1;
		}
		else
		{
			g_value = 1;
		}
		f_value = h_value + g_value;
		f_value *= WEIGHT;
	}
	MyTile* GetParent()
	{
		return parent;
	}
	friend bool operator<(MyTile t1, MyTile t2)	
	{
		return t1.f_value < t2.f_value;
	}
	friend bool operator==(MyTile t1, MyTile t2)
	{
		return t1.pos == t2.pos;
	}
	MyTile& operator= (MyTile t)
	{
		f_value = t.f_value;
		h_value = t.h_value;
		g_value = t.g_value;
		parent = t.parent;
		pos = t.pos;
		goal = t.goal;

		return *this;
	}

	/*~Tile() {}
	Tile& operator=(Tile& t)
	{
		f_value = t.f_value;
		h_value = t.h_value;
		g_value = t.g_value;

	}
	Tile() {}*/
};

#endif

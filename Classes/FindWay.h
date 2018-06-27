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
	int x;
	int y;
public:
	friend bool operator!= (Position a, Position b)
	{
		return !(a.x == b.x&&a.y == b.y);
	}
	Position operator=(const Position b)
	{
		x = b.x;
		y = b.y;
		return *this;
	}
	Position()
	{
		x = -1;
		y = -1;
	}
	Position(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	friend bool operator==(Position a, Position b)
	{
		return a.x == b.x&&a.y == b.y;
	}
};

class MyTile :public cocos2d::Ref
{
private:
	int f_value;
	int h_value;
	int g_value;
	MyTile* parent;
	Position pos;
	Position goal;
public:
	static MyTile* create(MyTile* _parent,const Position _pos,const Position _goal)
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
	Position GetPosition()
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

	void init(MyTile* _parent,const Position _pos,const Position _goal)
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
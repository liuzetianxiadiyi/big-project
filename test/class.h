#define WEIGHT 100;
#include <iostream>

using std::cout;
using std::endl;
class Position
{
public:
	int x;
	int y;
public:
	friend bool operator!= (Position a,Position b)
	{
		return !(a.x == b.x&&a.y == b.y);
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
class MyTile
{
public:
	int f_value;
	int h_value;
	int g_value;
	MyTile* parent;
	Position pos;
	Position goal;
public:
	bool available;
	bool inOpen;
	bool inClose;
	bool out;
	bool continuous;
public:
	MyTile()
	{
		f_value = 0;
		g_value = 0;
		h_value = 0;
		//parent = ;
		pos = Position();
		goal = Position();
	}
	MyTile(MyTile* _parent, Position _pos, Position _goal)
	{
		this->init(_parent, _pos, _goal);
	}
	void setOpen()
	{
		inOpen = true;
		inClose = false;
		out = false;
	}
	void setClose()
	{
		inOpen = false;
		inClose = true;
		out = false;
	}
	void serOut()
	{
		inOpen = false;
		inClose = false;
		out = true;
	}
	//ÒÑÐÞ¸Ä
	void set_hv()
	{
		int temp_x = goal.x - pos.x;
		int temp_y = goal.y - pos.y;
		h_value = (abs(temp_x) + abs(temp_y));
	}
	Position GetPosition()
	{
		return pos;
	}
	int Get_gv()
	{
		return g_value;
	}
	void init(MyTile* _parent, Position _pos, Position _goal)
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
	int getValue()
	{
		return f_value;
	}
	MyTile* GetParent()
	{
		return parent;
	}
	friend bool operator<(MyTile t1, MyTile t2)
	{
		//cout << "operator< " << endl;
		return t1.f_value < t2.f_value;
	}
	friend bool operator==(MyTile t1, MyTile t2)
	{
		return t1.pos == t2.pos;
	}
	//xiugai
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
};
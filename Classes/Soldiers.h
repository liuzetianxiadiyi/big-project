#ifndef __SOLDIERS_H__
#define __SOLDIERS_H__
#include"Military.h"
#include"Construction.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using std::string;
using namespace cocos2d::ui;


class Soldier : public Military
{
public:
	static string name;
	static int speed;
	static int delay;
	static Action* move;
	static int money;
	static int power;

public:
	static Soldier* create(string& filename);
	virtual void None() {};
};

class Dog : public Military
{
public:
	static string name;
	static int speed;
	static int delay;
	static Action* move;
	static int money;
	static int power;


public:
	static Dog* create(string& filename);
	virtual void None() {};
};

class Engineer : public Military
{
public:
	static string name;
	static int speed;
	static int delay;
	static Action* move;
	static int money;
	static int cure;
	static int power;
	
public:
	static Engineer* create(string& filename);
	virtual void None() {};
};
#endif

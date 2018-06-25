#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TestScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestScene);
};

#endif
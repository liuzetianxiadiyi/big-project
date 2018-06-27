
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"



class GameWin : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	//生命周期函数
	virtual bool init();

	// a selector callback
	void menuExitCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameWin);
};

#endif // __HELLOWORLD_SCENE_H__
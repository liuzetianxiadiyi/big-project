#ifndef __SETTING_SCENE_H_
#define __SETTING_SCENE_H_

#include "SystemHeader.h"
#include "cocos2d.h"
USING_NS_CC;
class Setting : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(Setting);
};

#endif
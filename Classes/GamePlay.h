#ifndef _GAMEPLAY_SCENE_H_
#define _GAMEPLAY_SCENE_H_

#include"cocos2d.h"

typedef enum
{
	army_Tag = 201
	, building_Tag
	, soilder_Tag
	,tank_tag
} SpriteTags;

class GamePlay :public
	cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	// ±øÖÖ½¨Öþ
	void armyCallback(cocos2d::Ref* pSender);
	void buildingCallback(cocos2d::Ref* pSender);
	void soilderCallback(cocos2d::Ref* pSender);
	void tankCallback(cocos2d::Ref* pSender);
	void baseCallback(cocos2d::Ref* pSender);
	void barracksCallback(cocos2d::Ref* pSender);
	void factoryCallback(cocos2d::Ref* pSender);
	//
	void menuContinueCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuGiveUpCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	CREATE_FUNC(GamePlay);
};
#endif //
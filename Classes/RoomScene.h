#ifndef __ROOMSCENE_H__
#define __ROOMSCENE_H__

#include<vector>
#include<iostream>
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using namespace cocos2d::ui;

class RoomScene:public cocos2d::Layer，public EditBoxDelegate,public ScrollViewDelegate
{
public:
	static Scene* createScene();

	bool init();

	void menuStartGameCallback(cocos2d::Ref* pSender);
	void menuDeleteRoomCallback(cocos2d::Ref* pSender);

	void CountryButtonCallback(cocos2d::Ref* pSender);
	void messageCallback(cocos2d::Ref* pSender);

	//begin
	virtual void onEnter();
	virtual void onExit();
    virtual bool init();
    
	vector<int> hides = { 2,3,5 };
	vector<int> show = { 1 };
	Vec2 chosen_position = { 500,500 };

	bool touchBegin(Touch* touch, Event* event);
	void touchMoved(Touch* touch, Event* event);
	void touchEnded(Touch* touch, Event* event);
	//Slider滑动事件回调函数
	void onChangedSlider(Ref* pSender, Slider::EventType type);
    
	//end
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	CREATE_FUNC(RoomScene);
};

#endif

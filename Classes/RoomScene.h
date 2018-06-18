#ifndef __ROOMSCENE_H__
#define __ROOMSCENE_H__

#include<vector>
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
	void messageCloseCallback(cocos2d::Ref* pSender);
	void CountryButtonCallback(cocos2d::Ref* pSender);	
    	
	//国家的button
	vector<Button*> hides;
	vector<Button*> show;

	//国家回调函数
	void countryCallBack(Ref* pSendre, Widget::TouchEventType type);
	void confirmCallBack(Ref* pSendre, Widget::TouchEventType type);
	
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
	
	void onChangedSlider2(Ref* pSender, Slider::EventType type);

	CREATE_FUNC(RoomScene);
};

#endif

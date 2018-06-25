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

class RoomScene:public cocos2d::Layer
{
public:
	static Scene* createScene();

	bool init();

	void recvThread();

	void menuStartGameCallback(cocos2d::Ref* pSender);
	void menuDeleteRoomCallback(cocos2d::Ref* pSender);
	void CountryButtonCallback(cocos2d::Ref* pSender);	
    	
	//国家的button
	vector<Button*> hides;
	vector<Button*> show;

	//国家回调函数
	void countryCallBack(Ref* pSendre, Widget::TouchEventType type);
	void confirmCallBack(Ref* pSendre, Widget::TouchEventType type);
	

	CREATE_FUNC(RoomScene);
};

#endif

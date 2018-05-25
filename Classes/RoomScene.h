#ifndef __ROOMSCENE_H__
#define __ROOMSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class RoomScene
{
public:
	static Scene* createScene();

	bool init();

	void menuStartGameCallback(cocos2d::Ref* pSender);
	void menuDeleteRoomCallback(cocos2d::Ref* pSender);

	void CountryButtonCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(RoomScene);
};

#endif
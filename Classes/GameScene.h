#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Military.h"
#include "Construction.h"
#include "FindWay.h"
#include <queue>

USING_NS_CC;

class GameScene:public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	vector<Military*> uVector;
	vector<Military*> sVector;
	vector<Construction*>  MyConstructions;
	Vec2 ViewPosition;
	const int ViewChangeSpeed = 50;	//´ýµ÷Õû
	vector<MyTile> closeTile;
	vector<MyTile> openTile;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(Vec2 position);
	
	virtual bool onMouseDown(cocos2d::Event * event);
	virtual void onMouseUp(cocos2d::Event* event);
	virtual void onMouseMove(cocos2d::Event* event);
	virtual void onMouseScroll(cocos2d::Event* event);
	void ButtonSettingCallback(Ref* pSender);
	virtual void onKeyPress(EventKeyboard::KeyCode keyCode, Event* event);

	//friend class Tile;
	vector<MyTile*> FindWay(Vec2 start, Vec2 goal);
	bool ColsCheck(Vec2 pos);

	CREATE_FUNC(GameScene);
};

#endif // !__GAMESCENE_H__

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Military.h"
#include <vector>

using std::vector;
USING_NS_CC;

class GameScene:public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	vector<Military*> uVector;
	vector<Military*> sVector;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(Vec2 position)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		int x = MAX(position.x, visibleSize.width / 2);
		int y = MAX(position.y, visibleSize.height / 2);
		x = MIN(x, (_tileMap->getMapSize().width*_tileMap->getTileSize().width) - visibleSize.width / 2);
		y = MIN(y, (_tileMap->getMapSize().height*_tileMap->getTileSize().height) - visibleSize.height / 2);

		Vec2 pointA = Vec2(visible)
	}

	CREATE_FUNC(GameScene);
};

#endif // !__GAMESCENE_H__

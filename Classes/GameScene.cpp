#include "GameScene.h"
#include "Constructions.h"
#include "SystemHeader.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create(".tmx");
	addChild(_tileMap, 0);
	//待调整
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("born");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	Base* sprite = Base::create("filename");
	sprite->setPosition(Vec2(x, y));
	addChild(sprite, 2);

	_collidable = _tileMap->getLayer("collodable");
	_collidable->setVisible(false);

	return true;
}

void GameScene::setPlayerPosition(Vec2(position))
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true")
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("");
			return;
		}

	}
	for (auto s : sVector)
	{
		//每个精灵的移动
	}
}

Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().setSize;

	return Vec2(x, y);
}
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
	//´ýµ÷Õû
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("born");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	Base* sprite = Base::create("filename");
	sprite->setPosition(Vec2(x, y));
	addChild(sprite, 2);

	_collidable = _tileMap->getLayer("collodable");
	_collidable->setVisible(false);

	//mouse chooose

	auto mouseListener = EventListenerTouchOneByOne::create();
	mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::MouseDown, this);
	mouseListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::MouseMoved, this);
	mouseListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::MouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ml,this);
	
	auto mouseChoose = Sprite::create("s.png");
	mouseChoose->setPosition(Vec2(0, 0));
	mouseChoose->setTag(10);
	mouseChoose->setAnchorPoint(Vec2(0, 0));
	this->addChild(s,10);

	//end
	
	return true;
}

//mouse choose

bool HelloWorld::MouseDown(Touch *touch, Event *unused_event)
{
	auto event = touch;
	Vec2 pos = event->getLocation();
	auto sprite = getChildByTag(10);
	sprite->setPosition(pos);

	return true;
}

void HelloWorld::MouseMoved(Touch *touch, Event *unused_event)
{
	auto event = touch;
	auto sprite = getChildByTag(10);
	Vec2 pos = event->getDelta() - sprite->getPosition();
	if (pos.x < 0)
		pos.x = -pos.x;
	if (pos.y < 0)
		pos.y = -pos.y;
	int x = pos.x;
	int y = pos.y;
	sprite->runAction(ScaleTo::create(0.1, x, y));
	std::cout << x << std::endl;
	std::cout << y << std::endl;
}

void HelloWorld::MouseUp(Touch *touch, Event *unused_event)
{
	
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
		//Ã¿¸ö¾«ÁéµÄÒÆ¶¯
	}
}

Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().setSize;

	return Vec2(x, y);
}

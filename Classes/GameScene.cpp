#include "GameScene.h"
#include "Constructions.h"
#include "SystemHeader.h"
#include "ui/CocosGUI.h"
#include "SettingScene.h"
#include <algorithm>

using namespace cocos2d::ui;
using std::find;
using std::reverse;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	auto Mouselistener = EventListenerMouse::create();

	Mouselistener->onMouseDown = GameScene::onMouseDown;
	Mouselistener->onMouseUp = GameScene::onMouseUp;
	Mouselistener->onMouseMove = GameScene::onMouseMove;
	Mouselistener->onMouseScroll = GameScene::onMouseScroll;

	EventDispather* eventDispather = Director::getInstance()->getEventDispatcher();
	eventDispather->addEventListenerWithSceneGraphPriority(Mouselistener, this);

	auto broadlistener = EventListenerKeyboard::create();
	broadlistener->onKeyPressed = GameScene::onKeyPress;
	eventDispather->addEventListenerWithSceneGraphPriority(broadlistener, this);
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

	Button* Set = Button::create("button.png", "buttonHighlight.png");
	Set->setScale9Enabled(true);
	Set->setPosition(Vec2(visibleSize.width - 100, 50));

	//设置button的监听器
	Set->addClickEventListener(CC_CALLBACK_1(GameScene::ButtonSettingCallback, this));
	this->addChild(Set, 3);

	Sprite* MenuBar = Sprite::create("filename");
	this->addChild(MenuBar,3);

	return true;
}

void GameScene::onKeyPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_KP_RIGHT)
	{
		ViewPosition.x += ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_LEFT)
	{
		ViewPosition.x -= ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_UP)
	{
		ViewPosition.y -= ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_KP_DOWN)
	{
		ViewPosition.y += ViewChangeSpeed;
	}
	setViewpointCenter(ViewPosition);
}

void GameScene::ButtonSettingCallback(Ref* pSender)
{
	
	auto scene = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

bool GameScene::ColsCheck(Vec2 position)
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
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}


Vec2 GameScene::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().setSize;

	return Vec2(x, y);
}

void GameScene::setViewpointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width*_tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height*_tileMap->getTileSize().height) - visibleSize.height / 2);

	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);

	Vec2 offset = pointA - pointB;

	this->setPosition(offset);
}

bool GameScene::onMouseDown(Event* event)
{
	log("onMouseDown");
}

void GameScene::onMouseMove(Event* event)
{
	log("onMouseMove");
}

void GameScene::onMouseScroll(Event* event)
{
	log("onMouseScroll");
}

void GameScene::onMouseUp(Event* event)
{
	EventMouse* em = dynamic_cast<EventMouse*> (event);
	EventMouse::MouseButton ButtonTag = em->getMouseButton();
	Vec2 pos = em->getLocationInView();
	if (ButtonTag == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		int x = _tileMap->getTileSize().width, y = _tileMap->getTileSize().height;
		for (auto& v : sVector)
		{
			Vec2 spritePos = v->getPosition();

			Vec2 diff = pos - spritePos;
			if (abs(diff.x) > abs(diff.y))
			{
				if (diff.x > 0)
				{
					v->runAction(FlipX::create(false));
				}
				else
				{
					x = -x;
					v->runAction(FlipX::create(true));
				}
			}
			else
			{
				if (diff.y < 0)
				{
					y = -y;
				}
			}
			v->runAction(MoveBy::create(v->getSpeed(), Vec2(x, y)));
		}
	}
	else if (ButtonTag == EventMouse::MouseButton::BUTTON_LEFT)
	{
		vector<Military*>::iterator it;
		for (it = sVector.begin();it!=sVector.end();++it)
		{
			uVector.push_back(*it);
			sVector.erase(it);
		}
		for (auto& c : MyConstructions)
		{
			if (c->getBoundingBox().containsPoint(pos))
			{
				Menu* menu = c->createMenu();
				menu->setPosition();
				this->addChild(menu, 3);
			}
		}
	}
}

vector<MyTile*> GameScene::FindWay(Vec2 start, Vec2 goal)
{
	MyTile* sta = MyTile::create(NULL, start, goal);
	openTile.push(*sta);
	Vec2 pos = start;
	while (pos != goal)
	{
		closeTile.push_back(openTile.top());
		openTile.pop();
		int flag_x, flag_y;
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{
			case 0:
				flag_x = 1;
				flag_y = 0;
				break;
			case 1:
				flag_x = 0;
				flag_y = 1;
				break;
			case 2:
				flag_x = -1;
				flag_y = 0;
				break;
			case 3:
				flag_x = 0;
				flag_y = -1;
				break;
			}
			pos.x += flag_x;
			pos.y += flag_y;
			if (ColsCheck(Vec2(pos.x, pos.y)))
			{
				Tile* nextWay = Tile::create(&openTile[0], Vec2(pos.x, pos.y), goal);
				vector<MyTile>::iterator iter;
				iter = find(closeTile.begin(), closeTile.end(), *nextWay);
				//is not in closeTile
				if (iter == closeTile.end())
				{
					vector<MyTile>::iterator it;
					it = find(openTile.begin(), openTile.end(), *nextWay);
					if (it != openTile.end())
					{
						if (*nextWay < *it)
						{
							*it = *nextWay;
							sort(openTile.begin(), openTile.end());
						}
					}
					else
					{
						openTile.push_back(*nextWay);
						sort(openTile.begin(), openTile.end());
					}
				}
			}
		}
		pos = openTil[0].GetPosition();
	}
	vector<Vec2> Way;
	Way.push_back(goal);
	MyTile& temp = closeTile[0];
	do
	{
		Way.push_back(temp.GetPosition());
		temp = *temp.GetParent();
	} while (temp.GetParent() != NULL);

	reverse(Way.cbegin(), Way.cend());

	return Way;
}

pair<Vec2, Vec2> Position::GetLocation(Vec2 point)
{
	return make_pair(Vec2(point.x % CHECKNUMS, point.y % CHECKNUMS), Vec2(point.x / CHECKNUMS, point.y / CHECKNUMS));
}

Vec2 Position::GetTopleft(Vec2 cpoint)
{
	return Vec2(cpoint.x*TILENUMS, cpoint.y*TILENUMS);
}

Vec2 Position::GetBelowleft(Vec2 cpoint)
{
	return Vec2(cpoint.x*TILENUMS, (cpoint.y + 1)*TILENUMS - 1);
}

Vec2 Position::GetTopright(Vec2 cpoint)
{
	return Vec2((cpoint.x + 1)*TILENUMS - 1, cpoint.y*TILENUMS);
}

Vec2 Position::GetBelowright(Vec2 cpoint)
{
	return Vec2((cpoint.x + 1)*TILENUMS - 1, (cpoint.y + 1)*TILENUMS - 1);
}
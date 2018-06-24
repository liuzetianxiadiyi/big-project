#include "GameScene.h"
#include "Constructions.h"
#include "SystemHeader.h"
#include "ui/CocosGUI.h"
#include "SettingScene.h"
#include <algorithm>
#include "GameData.h"
#include "enJsonParser.h"
#include "JsonParser.h"
#include <thread>
#include"Soldiers.h"
#include "FindWay.h"
//#include <mutex>
int tag = 1000;
using namespace cocos2d::ui;
using std::find;
using std::reverse;

Client* GameScene::client = Client::getInstance();

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	auto Mouselistener = EventListenerMouse::create();

	Mouselistener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown,this);
	Mouselistener->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
	Mouselistener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	Mouselistener->onMouseScroll = CC_CALLBACK_1(GameScene::onMouseScroll, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(Mouselistener, this);

	auto broadlistener = EventListenerKeyboard::create();
	broadlistener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPress, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(broadlistener, this);
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("untitled.tmx");
	addChild(_tileMap, 0);
	//待调整
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("born1");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	Sprite* sprite = Sprite::create("Base.png");
	sprite->setPosition(Vec2(x, y));

	this->addChild(sprite, 2);

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);


	Button* Set = Button::create("button.png", "buttonHighlight.png");
	Set->setScale9Enabled(true);
	Set->setPosition(Vec2(visibleSize.width - 100, 50));

	//设置button的监听器
	Set->addClickEventListener(CC_CALLBACK_1(GameScene::ButtonSettingCallback, this));
	this->addChild(Set, 3);

	Sprite* MenuBar = Sprite::create("MenuBar.png");

	/*thread SendThread = thread([&] {this->SendDataThread(); });
	SendThread.detach();
	thread RecvThread = thread([&] {this->RecvDataThread(); });
	RecvThread.detach();*/

	this->addChild(MenuBar,3);

	return true;
}

void GameScene::onKeyPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		ViewPosition.x += ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		ViewPosition.x -= ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		ViewPosition.y -= ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
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
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;

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
	return true;
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
	//wait to add click can move area
	if (ButtonTag == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		int x = _tileMap->getTileSize().width, y = _tileMap->getTileSize().height;
		for (auto& v : selectedMilitary)
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
			/*v->runAction(MoveBy::create(v->getSpeed(), Vec2(x, y)));*/
		}
	}
	else if (ButtonTag == EventMouse::MouseButton::BUTTON_LEFT)
	{
		selectedMilitary.insert(selectedMilitary.end(), unselectedMilitary.begin(), unselectedMilitary.end());
		unselectedMilitary.clear();
		for (auto& c : MyConstructions)
		{
			if (c->getBoundingBox().containsPoint(pos))
			{
				Menu* menu = c->createMenu();
				menu->setPosition(Vec2(100,100));
				this->addChild(menu, 3);
			}
		}
	}
}

bool GameScene::ConstructionCheck(Vec2 pos)
{
	for (auto& c : MyConstructions)
	{
		if (c->getBoundingBox().containsPoint(pos))
		{
			return false;
		}
	}
	return true;
}

vector<Position> GameScene::FindWay(Position start, Position goal)
{
	//create start Tile
	MyTile* sta = MyTile::create(NULL, start, goal);

	closeTile.push_back(*sta);
	Position pos = start;
	//count use to juggle if the Tile is added newly
	int count = 0;
	while (pos != goal)
	{
		//used to get different direction Tile
		int flag_x, flag_y;
		bool flag = false;
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
			Position temp;
			temp.x = pos.x + flag_x;
			temp.y = pos.y + flag_y;
			//Check collision
			if (ColsCheck(Vec2(temp.x,temp.y)) && ConstructionCheck(Vec2(temp.x, temp.y)))
			{
				MyTile* nextWay = MyTile::create(&openTile[0], temp, goal);
				vector<MyTile>::iterator iter;
				iter = find(closeTile.begin(), closeTile.end(), *nextWay);
				//is not in closeTile
				if (iter == closeTile.end())
				{
					flag = true;	//find an available way
					vector<MyTile>::iterator it;
					it = find(openTile.begin(), openTile.end(), *nextWay);
					if (it != openTile.end())
					{
						if (*nextWay < *it)
						{
							*it = *nextWay;
						}
					}
					else
					{
						openTile.push_back(*nextWay);
					}
				}
			}
		}
		/*if flag==true ,it means that this way is available
		if not , it means that there is no way to use
		so keep the impasse in closeTile
		and the make pos = the position of the Tile whose child is added in closeTile latest
		(because the added in closeTile latest one is impasse)
		and then find again*/
		if (flag)
		{
			sort(openTile.begin(), openTile.end());
			pos = openTile.begin()->GetPosition();
			//choose the best one as the nextway
			closeTile.push_back(*openTile.begin());
			//delete it from the vector of choices
			openTile.erase(openTile.begin());
			++count;
			flag = false;
		}
		else
		{
			pos = closeTile[closeTile.size() - 1].GetParent()->GetPosition();
		}
	}
	//put the finded way in a vector
	vector<Position> Way;
	Way.push_back(goal);
	MyTile* temp = &closeTile[closeTile.size() - 1];
	do
	{
		Way.push_back(temp->GetPosition());
		temp = temp->GetParent();
	} while (temp!= NULL);

	reverse(Way.begin(), Way.end());

	return Way;
}

//
//pair<Vec2, Vec2> Position::GetLocation(Vec2 point)
//{
//	return make_pair(Vec2(int(point.x) % CHECKNUMS, int(point.y) % CHECKNUMS), Vec2(point.x / CHECKNUMS, point.y / CHECKNUMS));
//}
//
//Vec2 Position::GetTopleft(Vec2 cpoint)
//{
//	return Vec2(cpoint.x*TILENUMS, cpoint.y*TILENUMS);
//}
//
//Vec2 Position::GetBelowleft(Vec2 cpoint)
//{
//	return Vec2(cpoint.x*TILENUMS, (cpoint.y + 1)*TILENUMS - 1);
//}
//
//Vec2 Position::GetTopright(Vec2 cpoint)
//{
//	return Vec2((cpoint.x + 1)*TILENUMS - 1, cpoint.y*TILENUMS);
//}
//
//Vec2 Position::GetBelowright(Vec2 cpoint)
//{
//	return Vec2((cpoint.x + 1)*TILENUMS - 1, (cpoint.y + 1)*TILENUMS - 1);
//}

void GameScene::SendDataThread()
{
	while (true)
	{
		mtx.lock();

		enJsonParser* json = enJsonParser::createWithArray(GameData::MilitaryData(unselectedMilitary));
		string sendBuf = json->encode_MilitaryData();
		GameScene::client->send_Cli(sendBuf);

		mtx.unlock();
		Sleep(TIME_LAG);
	}
}

void GameScene::RecvDataThread()
{
	using namespace encode_MilitaryData;
	using namespace encode_ConstructionData;
	while (true)
	{
		mtx.lock();
		//receive message
		string recvBuf = client->recv_Cli();
		//parser message
		JsonParser* json = JsonParser::createWithC_str(recvBuf.c_str());
		ValueMap Gamedata = json->decode_GameData();

		ValueMap MilitaryVector = Gamedata[MILITARYDATA].asValueMap();
		ValueMap ConstructionVectror = Gamedata[CONSTRUCTIONDATA].asValueMap();

		ValueVector dogdata;
		ValueVector soldierdata;
		ValueVector engineerdata;

		dogdata = MilitaryVector[DOGDATA].asValueVector();
		soldierdata = MilitaryVector[SOLDIERDATA].asValueVector();
		engineerdata = MilitaryVector[ENGINEERDATA].asValueVector();

		this->updateMilitary(dogdata,Dog_Data);
		this->updateMilitary(soldierdata,Soldier_Data);
		this->updateMilitary(engineerdata,Engineer_Data);

		ValueVector bardata;
		ValueVector wardata;
		ValueVector mindata;
		ValueVector basdata;

		bardata = ConstructionVectror[BARRACKSDATA].asValueVector();
		wardata = ConstructionVectror[WARFACTORYDATA].asValueVector();
		mindata = ConstructionVectror[MINEDATA].asValueVector();
		basdata = ConstructionVectror[BASEDATA].asValueVector();

		this->updateConstruction(bardata, Bar_Data);
		this->updateConstruction(wardata, War_Data);
		this->updateConstruction(mindata, Min_Data);
		this->updateConstruction(basdata, Bas_Data);

		mtx.unlock();
	}
}

void GameScene::updateMilitary(ValueVector& valuevector,int type)
{
	//in GameData.h
	using namespace encode_MilitaryData;
	for (auto& v : valuevector)
	{
		// one military's information
		ValueMap map = v.asValueMap();
		int spriteTag = map[STAG].asInt();
		Military* sprite = dynamic_cast<Military*>(this->getChildByTag(spriteTag));
		if (sprite)
		{
			sprite->sethp(map[HEALTHPOINT].asInt());
			sprite->setPosition(Vec2(map[POSITIONX].asInt(), map[POSITIONY].asInt()));
			sprite->setDestination(Vec2(map[DESTINATIONX].asInt(), map[DESTINATIONY].asInt()));
			sprite->setStatus(map[STATUS].asString().c_str());
		}
		else
		{
			if (type == Dog_Data)
			{
				sprite = Dog::create("Dog.png");	//filename modify to staitc member variable
			}
			else if (type == Soldier_Data)
			{
				sprite = Soldier::create("Soldier.png");
			}
			else if (type == Engineer_Data)
			{
				sprite = Engineer::create("Engineer.png");
			}
			//sprite->init();
			this->addChild(sprite, tag, 3);
		}
	}
}

void GameScene::updateConstruction(ValueVector& valuevector, int type)
{
	using namespace encode_ConstructionData;
	for (auto& v : valuevector)
	{
		ValueMap map = v.asValueMap();
		int spriteTag = map[STAG].asInt();
		Construction* sprite = dynamic_cast<Construction*>(this->getChildByTag(spriteTag));
		if (sprite)
		{
			sprite->sethp(map[HEALTHPOINT].asInt());
			sprite->setPosition(Vec2(map[POSITIONX].asInt(), map[POSITIONY].asInt()));
		}
		else
		{
			if (type == Bar_Data)
			{
				sprite = Barracks::create("Barrscks.png");	//filename modify to staitc member variable
			}
			else if (type == War_Data)
			{
				sprite = Warfactory::create("Warfactory.png");
			}
			else if (type == Min_Data)
			{
				sprite = Mine::create("Mine.png");
			}
			else if (type == Bas_Data)
			{
				sprite = Base::create("Base.png");
			}
			//sprite->init();
			this->addChild(sprite, tag, 3);
		}
	}
}
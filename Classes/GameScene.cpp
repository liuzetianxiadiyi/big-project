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
#include "time.h"
#include <vector>
#include <string>
USING_NS_CC;
using std::string;
using std::vector;

string words;
int i = 204;
int flag = 1;
int labelcount = 500;
vector<string> news;

//gamescene layer tag = 1
//#include <mutex>
int tag = 1000;
using namespace cocos2d::ui;
using std::find;
using std::reverse;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer,1,1);
	return scene;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	auto Mouselistener = EventListenerMouse::create();

	Mouselistener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
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
	//待调整
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("born1");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	log("mapPosition x= %f,y=%f", _tileMap->getPosition().x, _tileMap->getPosition().y);
	//_tileMap->setPosition(Vec2(-x + visibleSize.width / 2, -y + visibleSize.height / 2));
	addChild(_tileMap, 0);
	setViewpointCenter(Vec2(-320, -1600));

	Base* sprite = Base::create("Base.png");
	sprite->setPosition(Vec2(x, y));
	MyConstructions.push_back(sprite);
	log("Base position x=%f.=%f", sprite->getPosition().x, sprite->getPosition().y);
	Rect rec = sprite->getBoundingBox();
	log("BaseBound maxx=%f,maxy=%f,minx=%f,miny=%f", rec.getMaxX(), rec.getMaxY(), rec.getMinX(), rec.getMinY());

	this->addChild(sprite, 2);

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	//this->schedule(schedule_selector(GameScene::SendDataThread), 1, -1, 2);
	//this->schedule(schedule_selector(GameScene::RecvDataThread), 1, -1, 2);
	//Button* Set = Button::create("button.png", "buttonHighlight.png");
	//Set->setScale9Enabled(true);
	//Set->setPosition(Vec2(visibleSize.width - 100, 50));

	////设置button的监听器
	//Set->addClickEventListener(CC_CALLBACK_1(GameScene::ButtonSettingCallback, this));
	//this->addChild(Set, 3);

	//Sprite* MenuBar = Sprite::create("MenuBar.png");

	///*thread SendThread = thread([&] {this->SendDataThread(); });
	//SendThread.detach();
	//thread RecvThread = thread([&] {this->RecvDataThread(); });
	//RecvThread.detach();*/

	//this->addChild(MenuBar,3);

	//smap = Sprite::create("untitle.png");
	//smap->setPosition(Vec2(visibleSize.width, visibleSize.height));

	//addChild(smap, 3);


	////聊天框
	//auto MessageItem = MenuItemImage::create(
	//	"pastmessage.png",
	//	"pastmessage.png",
	//	CC_CALLBACK_1(GameScene::messageCallback, this)
	//);

	//if (MessageItem == nullptr ||
	//	MessageItem->getContentSize().width <= 0 ||
	//	MessageItem->getContentSize().height <= 0)
	//{
	//	
	//}
	//else
	//{
	//	float x = visibleSize.width - 2 * (MessageItem->getContentSize().width);
	//	float y = 2 * MessageItem->getContentSize().height - 50;
	//	MessageItem->setPosition(Vec2(x, y));
	//}

	//// create menu, it's an autorelease object
	//auto menu2 = Menu::create(MessageItem, NULL);
	//menu2->setPosition(Vec2::ZERO);
	//this->addChild(menu2, 1);

	//auto pEditBox_name = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("text2.png"));
	//pEditBox_name->setPosition(ccp(visibleSize.width * 1 / 3, visibleSize.height * 1 / 5));
	//pEditBox_name->setFontColor(Color3B(0, 0, 0));//设置字体颜色  
	//pEditBox_name->setFont("Arial", 20);
	//pEditBox_name->setPlaceHolder("Input: ");//设置预置文本    
	//pEditBox_name->setMaxLength(160);//设置最大长度    
	//pEditBox_name->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);//可以输入任何，但是不包括换行   
	//pEditBox_name->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位    
	//pEditBox_name->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型    
	//pEditBox_name->setDelegate(this);//当前类继承CCEditBoxDelegate类    
	//pEditBox_name->setTag(101);
	//this->addChild(pEditBox_name, 2);

	//Sprite * Accont_back = Sprite::create("accont-back.png");

	//Accont_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//this->addChild(Accont_back, 1);

	//账号框
	//auto editbox = EditBox::create(Size(200, 35), Scale9Sprite::create("editbox.png"));
	//editbox->setAnchorPoint(Point(0, 0));
	//editbox->setPosition(Point(visibleSize.width *0.3, visibleSize.height*0.55));
	//editbox->setPlaceHolder("name:");//占位字符  
	//editbox->setMaxLength(8000);
	//editbox->setFontColor(Color3B::BLACK);//设置输入字体的颜色  
	//editbox->setText("player");
	//editbox->setTag(1);
	//this->addChild(editbox, 2);

	////创建Button
	//auto button = Button::create("button.png", "buttonHighlight.png");

	//button->setScale9Enabled(true);
	//button->setTitleText("OK");
	//button->setTitleFontSize(35);
	//button->setContentSize(Size(100, 20));
	//button->setPosition(Vec2(visibleSize.width - 100, 50));

	////设置button的监听器
	////button->addClickEventListener(CC_CALLBACK_1(AccontScene::buttonOkCallback, this));

	//this->addChild(button, 2);
	return true;
}


void GameScene::messageCallback(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("pastnews.png");
	sprite->setTag(498);
	if (sprite == nullptr)
	{

	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 40));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::messageCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{

	}
	else
	{
		float x = origin.x + visibleSize.width / 2 + closeItem->getContentSize().width / 2;
		float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1, 497);


	for (int j = i; j >= i - 12; j--)
	{
		this->removeChildByTag(j);
	}
	int count = 0;

	labelcount = 500;
	for (vector<string>::iterator iter1 = news.begin(); iter1 != news.end(); iter1++)
	{
		auto label = Label::createWithTTF(*iter1, "fonts/Marker Felt.ttf", 24);
		if (label == nullptr)
		{

		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 100 - count * 30));

			// add the label as a child to this layer
			this->addChild(label, 1, labelcount);
		}
		++count;
		++labelcount;
	}
	++flag;

	//创建滑块控件
	Slider* slider = Slider::create();
	//加载滑杆纹理
	slider->loadBarTexture("sliderTrack.png");
	//加载滑块按钮纹理
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	//加载滑块进度栏纹理
	slider->loadProgressBarTexture("sliderProgress.png");
	//The max percent of Slider.
	slider->setMaxPercent(100);
	slider->setRotation(90);

	slider->setPosition(Vec2(visibleSize.width / 2.0f + 60, visibleSize.height / 2.0f));
	slider->addEventListener(CC_CALLBACK_2(GameScene::onChangedSlider2, this));
	this->addChild(slider, 1, 499);

}
//聊天框发送信息
void GameScene::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
	auto editbox = (EditBox*)editBox;

	if (editBox->getTag() == 101)
	{
		// 获取系统时间
		time_t now;
		struct tm *time1;

		now = time(NULL);

		time1 = localtime(&now);      //microseconds: 微秒
		int year = time1->tm_year + 1900;
		log("year = %d", year);         //显示年份
		asctime(time1);
		char date1[32] = { 0 };
		sprintf(date1, "%d %02d %02d", (int)time1->tm_year + 1900, (int)time1->tm_mon + 1, (int)time1->tm_mday);
		log("%s", date1);        //显示年月日

		char date2[50] = { 0 };
		sprintf(date2, "%02d %02d %02d", (int)time1->tm_hour, (int)time1->tm_min, (int)time1->tm_sec);
		log("%s", date2);       //显示时分秒

								//auto label2 = Label::createWithTTF(asctime(time1), "fonts/Marker Felt.ttf", 24);

		news.push_back(asctime(time1));

		news.push_back(words);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto label = Label::createWithTTF(words, "fonts/Marker Felt.ttf", 24);
		if (label == nullptr)
		{

		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(ccp(visibleSize.width * 1 / 5, visibleSize.height * 5 / 6 - (label->getContentSize().height*(i % 12))));
			// add the label as a child to this layer
			this->addChild(label, 1, i);
			this->removeChildByTag(i - 12);
			i = i + 1;
		}
		auto label2 = Label::createWithTTF(asctime(time1), "fonts/Marker Felt.ttf", 24);
		if (label2 == nullptr)
		{

		}
		else
		{
			// position the label on the center of the screen
			label2->setPosition(ccp(visibleSize.width * 2 / 5, (visibleSize.height * 5 / 6 + 2 * (label->getContentSize().height) - (label->getContentSize().height*(i % 12))) - 6));
			// add the label as a child to this layer
			this->addChild(label2, 1, i);
			this->removeChildByTag(i - 12);
			i = i + 1;
		}
		editBox->setText("");

	}
	if (editBox->getTag() == 102)
	{
		editBox->setText("you recieved a letter");
	}
}
void GameScene::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}


void GameScene::editBoxEditingDidEnd(EditBox *editBox)

{
	CCLOG("end edit");
}

void GameScene::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	CCLOG("EditBox_password changed");
	auto editbox = (EditBox*)editBox;
	if (editBox->getTag() == 101)
	{
		words = text;
	}
	if (editbox->getTag() == 102)
	{
		editBox->setText("");

	}

}
void GameScene::onChangedSlider2(Ref* pSender, Slider::EventType type)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{

		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent() * 5;
		for (int m = 500; m < labelcount; m++)
		{
			auto label1 = getChildByTag(m);
			label1->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 100 - 30 * (m - 500) + percent
			)));

		}
	}
}

void GameScene::onKeyPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		ViewPosition.x -= ViewChangeSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		ViewPosition.x += ViewChangeSpeed;
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
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width*_tileMap->getTileSize().width) - visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height*_tileMap->getTileSize().height) - visibleSize.height / 2);
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);
	Vec2 offset = pointA - pointB;*/
	if (position.x > 0)
	{
		position.x = 0;
	}
	else if (position.x < -1632)
	{
		position.x = -1632;
	}
	if (position.y > 0)
	{
		position.y = 0;
	}
	else if (position.y<-1824)
	{
		position.y = -1824;
	}
	log("view x=%f,y=%f", position.x, position.y);
	this->setPosition(position);
}

bool GameScene::onMouseDown(Event* event)
{

	EventMouse* em = dynamic_cast<EventMouse*> (event);

	BeginLocation = em->getLocation();

	log("onMouseDown");
	return true;
}

void GameScene::onMouseMove(Event* event)
{
	//log("onMouseMove");
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
	log("click x =%f,y = %f", pos.x, pos.y);
	bool sFlag = false;
	vector<Vec2> way;
	Vec2 start, goal;
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
			float speed;
			if (typeid(*v) == typeid(Dog))
			{
				speed = Dog::speed;
			}
			else if (typeid(*v) == typeid(Soldier))
			{
				speed = Soldier::speed;
			}
			else if (typeid(*v) == typeid(Engineer))
			{
				speed = Engineer::speed;
			}
			start = tileCoordFromPosition(v->getPosition());
			goal = tileCoordFromPosition(pos);
			way = FindWay(start, goal);
			for (auto w : way)
			{
				v->runAction(MoveBy::create(speed, w));
			}
			
		}
	}
	else if (ButtonTag == EventMouse::MouseButton::BUTTON_LEFT)
	{
		int i = 1;
		while (i)
		{
			Vec2 EndLocation = pos;
			if (abs(EndLocation.x - BeginLocation.x)<10 && abs(EndLocation.y - BeginLocation.y))
			{
				break;
			}
			Rect rect = Rect(BeginLocation.x, EndLocation.y, EndLocation.x - BeginLocation.x, BeginLocation.y - EndLocation.y);
			for (auto& v : unselectedMilitary)
			{
				Vec2 spritePos = v->getPosition();
				if (rect.containsPoint(spritePos))
				{
					v->setSelected(true);
					selectedMilitary.push_back(v);
				}
			}
			--i;
		}
		if (i)
		{
			unselectedMilitary.insert(unselectedMilitary.end(), selectedMilitary.begin(), selectedMilitary.end());
			selectedMilitary.clear();
			for (auto& c : MyConstructions)
			{
				if (c->getBoundingBox().containsPoint(pos))
				{
					sFlag = true;
					log("click a construction");
					Menu* menu = c->createMenu();
					menu->setPosition(Vec2(100, 100));
					this->addChild(menu, 3);
				}
			}
			//	if (smap->getBoundingBox().containsPoint(pos))
			//	{
			//		sFlag = true;
			//		Vec2 mapPos = smap->getPosition();
			//		int x = pos.x - mapPos.x;
			//		int y = pos.y - mapPos.y;
			//		/*double xx = x / length;
			//		double yy = y / length;
			//		setViewpointCenter(Vec2(xx*(_tileMap->getMapSize().width*_tileMap->getTileSize().width), yy*(_tileMap->getMapSize().height*_tileMap->getTileSize().height)));
			//*/	}
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

vector<Vec2> GameScene::FindWay(Vec2 start, Vec2 goal)
{
	//create start Tile
	MyTile* sta = MyTile::create(NULL, start, goal);

	closeTile.push_back(*sta);
	Vec2 pos = start;
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
			Vec2 temp;
			temp.x = pos.x + flag_x;
			temp.y = pos.y + flag_y;
			//Check collision
			if (ColsCheck(Vec2(temp.x, temp.y)) && ConstructionCheck(Vec2(temp.x, temp.y)))
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
	vector<Vec2> Way;
	Way.push_back(goal);
	MyTile* temp = &closeTile[closeTile.size() - 1];
	do
	{
		Way.push_back(temp->GetPosition());
		temp = temp->GetParent();
	} while (temp != NULL);

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

void GameScene::SendDataThread(float td)
{
	Client* client = Client::getInstance();
	
	enJsonParser* json = enJsonParser::createWithArray(GameData::MilitaryData(unselectedMilitary));
	string sendBuf = json->encode_MilitaryData();
	client->send_Cli(sendBuf);

	enJsonParser* json2 = enJsonParser::createWithArray(GameData::ConstructionData(MyConstructions));
	string sendBuf2 = json->encode_ConstructionData();
	client->send_Cli(sendBuf2);

}

void GameScene::RecvDataThread(float td)
{
	using namespace encode_MilitaryData;
	using namespace encode_ConstructionData;

	Client* client = Client::getInstance();
	//receive message
	string recvBuf = client->recv_Cli();
	//parser message
	int pos = 0;
	int begin;
	while (pos != -1)
	{
		begin = pos;
		pos = recvBuf.find('|',pos);
		string substr = recvBuf.substr(begin, pos);
		cout << "recvBuf's substr = "<< substr << endl;
		++pos;
		JsonParser* json = JsonParser::createWithC_str(substr.c_str());
		ValueMap Gamedata = json->decode_GameData();

		ValueMap MilitaryVector = Gamedata[MILITARYDATA].asValueMap();
		ValueMap ConstructionVectror = Gamedata[CONSTRUCTIONDATA].asValueMap();

		ValueVector dogdata;
		ValueVector soldierdata;
		ValueVector engineerdata;

		dogdata = MilitaryVector[DOGDATA].asValueVector();
		soldierdata = MilitaryVector[SOLDIERDATA].asValueVector();
		engineerdata = MilitaryVector[ENGINEERDATA].asValueVector();

		this->updateMilitary(dogdata, Dog_Data);
		this->updateMilitary(soldierdata, Soldier_Data);
		this->updateMilitary(engineerdata, Engineer_Data);

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

	}

}

void GameScene::updateMilitary(ValueVector& valuevector, int type)
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
			this->addChild(sprite, 3, tag);
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
			this->addChild(sprite, 3,tag);
		}
	}
}

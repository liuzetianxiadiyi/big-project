#include "HelloWorldScene.h"
#include "WaitingScene.h"
#include "RoomScene.h"
#include "GameData.h"
#include "Client.h"
#include "JsonParser.h"
#include "enJsonParser.h"

#include <string>

#define ROOMBUTTONWIDTH 60

extern Information information;
//待完善
int WaitingScene::room_nums = 0;
int WaitingScene::SelectedRoomTag = -1;
bool WaitingScene::replace = false;

Scene* WaitingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}

bool WaitingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	replace = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	thread roomThread(this->roomDataThread);
	roomThread.detach();

	auto EnterItem = MenuItemImage::create(
		"EnterNormal.png",
		"EnterSelected.png",
		CC_CALLBACK_1(WaitingScene::menuEnterCallback, this)
	);
	EnterItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));		//美工了解一下
	
	//create a slider
	auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_Back.png");

	slider->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));//我自己了解一下
	slider->setRotation(90);//不能实现竖条，只能旋转实现

	//slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
	//	switch (type)
	//	{
	//	case ui::Widget::TouchEventType::BEGAN:
	//		break;
	//	case ui::Widget::TouchEventType::ENDED:
	//		std::cout << "slider moved" << std::endl;
	//		break;
	//	default:
	//		break;
	//	}
	//});//貌似是个监听函数，但是我看不懂意思

	this->addChild(slider);

	auto createRoomItem = MenuItemImage::create(
		"createRoomNormal.png",
		"createRoomSelected.png",
		CC_CALLBACK_1(WaitingScene::createRoomCallback, this)
	);
	createRoomItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));

	auto ReturnItem = MenuItemImage::create(
		"ReturnNormal.png",
		"ReturnSelected.png",
		CC_CALLBACK_1(WaitingScene::menuReturnCallback, this)
	);
	ReturnItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));

	auto menu = Menu::create(EnterItem, createRoomItem, ReturnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create(".png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	return true;
}

void WaitingScene::roomDataThread()
{
	rmtx.lock();
	while (!replace)
	{
		Client* client = Client::getInstance();
		if (client->recv_Cli())
		{
			rmtx.lock();

			JsonParser json(information.getRecvBuf().c_str());
			json.decode();
			ValueMap DataMap = json.getList().at(0).asValueMap();		//0 is default position
			if (DataMap.find(WAITINGSCENEDATA) != DataMap.end())
			{
				ValueMap Data = DataMap[WAITINGSCENEDATA].asValueMap();

				room_nums = Data[ADDROOM].asInt();

				ValueVector room_tag = Data[ROOMLABEL].asValueVector();

				bool isDeleted = Data[DELETED].asBool();

				if (isDeleted)
				{
					ValueVector DeletedRoom = Data[DELETEDROOM].asValueVector();
					for (int i = 0; i < DeletedRoom.size(); ++i)
					{
						removeChildByTag(DeletedRoom[i].asInt());
					}
				}

				for (int i = 0; i < room_nums; ++i)
				{
					auto roomButton = Button::create("room.png", "roomHighlight.png");
					//美工
					roomButton->setScale9Enabled(true);
					roomButton->setTitleText(to_string(room_tag.at(i).asInt()));
					roomButton->setTitleFontSize(35);
					roomButton->setContentSize(Size(100, 20));
					roomButton->setPosition(Vec2(visibleSize.width - 100, 50));

					roomButton->addClickEventListener(CC_CALLBACK_1(WaitingScene::clickRoomcallback, this));

					roomButton->setTag(i);
					this->addChild(roomButton, 2);
				}
			}

			rmtx.unlock();
		}
		Sleep(2*TIME_LAG);
	}
	rmtx.unlock();
}

void WaitingScene::menuEnterCallback(Ref* pSender)
{
	if (SelectedRoomTag != -1)
	{
		UserDefault* defaults = UserDefault::getInstance();
		//send room_tag and player of this room message
		ValueVector plistdata = GameData::WaitingData(false, SelectedRoomTag, defaults->getStringForKey(PLAYERNAME));

		rmtx.lock();
		replace = true;

		enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
		enJson->encode(information, ENTERROOMDATA);
		Client* client = Client::getInstance();
		client->send_Cli();

		rmtx.unlock();
		//Scene changes
		auto scene = RoomScene::createScene();
		auto reScene = TransitionJumpZoom::create(1.0f, scene);
		Director::getInstance()->replaceScene(reScene);
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::getInstance()->playEffect("filename");
		}
	}
}

void WaitingScene::createRoomCallback(Ref* pSender)
{
	rmtx.lock();

	replace = true;

	rmtx.unlock();

	UserDefault* defaults = UserDefault::getInstance();
	//send room_tag and player of this room message

	ValueVector plistdata = GameData::WaitingData(true, SelectedRoomTag, defaults->getStringForKey(PLAYERNAME));

	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	enJson->encode(information, ENTERROOMDATA);

	Client* client = Client::getInstance();
	client->send_Cli();

	rmtx.unlock();

	auto scene = RoomScene::createScene(); 
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

void WaitingScene::menuReturnCallback(Ref* pSender)
{
	rmtx.lock();
	replace = true;

	auto scene = HelloWorld::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

void WaitingScene::clickRoomcallback(Ref* pSender)
{
	Button* SelectedRoom = dynamic_cast<Button*>(pSender);

	if (SelectedRoom->isHighlighted())
	{
		menuEnterCallback(pSender);
	}
	else
	{
		for (int i = 0; i < room_nums; ++i)
		{
			Button* roombutton = (Button*)this->getChildByTag(i);
			roombutton->setHighlighted(false);
		}
		SelectedRoom->setHighlighted(true);
		SelectedRoomTag = SelectedRoom->getTag();
	}
	
}

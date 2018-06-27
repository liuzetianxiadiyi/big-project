#include "HelloWorldScene.h"
#include "WaitingScene.h"
#include "RoomScene.h"
#include "GameData.h"
#include "Client.h"
#include "JsonParser.h"
#include "enJsonParser.h"
#include "SystemHeader.h"
#include <mutex>

#include <string>

#define ROOMBUTTONWIDTH 60

//待完善
int WaitingScene::SelectedRoomTag = -1;
bool WaitingScene::replace = false;
mutex mtx;

Scene* WaitingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WaitingScene::create();
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
	room_nums = 10;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	thread roomThread([&] {this->roomDataThread(); });
	roomThread.detach();

	auto EnterItem = MenuItemImage::create(
		"EnterNormal.png",
		"EnterSelected.png",
		CC_CALLBACK_1(WaitingScene::menuEnterCallback, this)
	);
	EnterItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2 + 60));	//美工了解一下

	auto createRoomItem = MenuItemImage::create(
		"createRoomNormal.png",
		"createRoomSelected.png",
		CC_CALLBACK_1(WaitingScene::createRoomCallback, this)
	);
	createRoomItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2));

	auto ReturnItem = MenuItemImage::create(
		"ReturnNormal.png",
		"ReturnSelected.png",
		CC_CALLBACK_1(WaitingScene::menuReturnCallback, this)
	);
	ReturnItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2 - 60));

	auto menu = Menu::create(EnterItem, createRoomItem, ReturnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("accont-back.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	//Slider* slider = Slider::create();
	//	//加载滑杆纹理
	//	slider->loadBarTexture("sliderTrack.png");
	//	//加载滑块按钮纹理
	//	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	//	//加载滑块进度栏纹理
	//	slider->loadProgressBarTexture("sliderProgress.png");
	//	//The max percent of Slider.
	//	slider->setMaxPercent(100);
	//	slider->setRotation(90);
	//
	//	slider->setPosition(Vec2(visibleSize.width / 2.0f + 60, visibleSize.height / 2.0f));
	//	//slider->addEventListener(CC_CALLBACK_2(WaitingScene::onChangedSlider, this));
	//	this->addChild(slider, 1);
	//room_nums = 10;
	//for (int i = 0; i < room_nums; ++i)
	//{
	//	auto visibleSize = Director::getInstance()->getVisibleSize();
	//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//	auto roomButton = Button::create("room.png", "roomHighlight.png");
	//	//美工
	//	roomButton->setScale9Enabled(true);
	//	roomButton->setTitleText(to_string(i));
	//	roomButton->setTitleFontSize(20);
	//	roomButton->setContentSize(Size(100, 20));
	//	roomButton->setPosition(Vec2(visibleSize.width - 300, 50 + i * 25));

	//	roomButton->addClickEventListener(CC_CALLBACK_1(WaitingScene::clickRoomcallback, this));

	//	roomButton->setTag(i);
	//	this->addChild(roomButton, 2);
	//}
	for (int i = 0; i < room_nums; ++i)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto roomButton = Button::create("room.png", "roomHighlight.png");
		//美工
		roomButton->setScale9Enabled(true);
		roomButton->setTitleText(to_string(i));
		roomButton->setTitleFontSize(24);
		roomButton->setContentSize(Size(100, 20));
		roomButton->setPosition(Vec2(visibleSize.width - 300, 50 + i * 25));

		roomButton->addClickEventListener(CC_CALLBACK_1(WaitingScene::clickRoomcallback, this));

		roomButton->setTag(i);
		this->addChild(roomButton, 2);
	}

	return true;
}

void WaitingScene::roomDataThread()
{
	//mtx.lock();
	//while (!replace)
	//{
	//	Client* client = Client::getInstance();
	//	string information;
	//	if ((information = client->recv_Cli()) != "")
	//	{
	//		log("information=%s", information);
	//		JsonParser* json = JsonParser::createWithC_str(information.c_str());
	//		ValueMap DataMap = json->decode_WaitingData();
	//		if (DataMap.find(SWAITINGSCENEDATA) != DataMap.end())
	//		{
	//			ValueMap Data = DataMap[SWAITINGSCENEDATA].asValueMap();

	//			room_nums = Data[ADDROOM].asInt();
	//			log("roomNums=%d", room_nums);

	//			ValueVector room_tag = Data[ROOMLABEL].asValueVector();

	//			
	//			for (int i = 0; i < room_nums; ++i)
	//			{
	//				auto visibleSize = Director::getInstance()->getVisibleSize();
	//				Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//				auto roomButton = Button::create("room.png", "roomHighlight.png");
	//				//美工
	//				roomButton->setScale9Enabled(true);
	//				roomButton->setTitleText(to_string(i));
	//				roomButton->setTitleFontSize(20);
	//				roomButton->setContentSize(Size(100, 20));
	//				roomButton->setPosition(Vec2(visibleSize.width - 300, 50 + i * 25));

	//				roomButton->addClickEventListener(CC_CALLBACK_1(WaitingScene::clickRoomcallback, this));

	//				roomButton->setTag(i);
	//				this->addChild(roomButton, 2);
	//			}

	//			bool isDeleted = Data[DELETED].asBool();

	//			if (isDeleted)
	//			{
	//				ValueVector DeletedRoom = Data[DELETEDROOM].asValueVector();
	//				for (int i = 0; i < DeletedRoom.size(); ++i)
	//				{
	//					removeChildByTag(DeletedRoom[i].asInt());
	//				}
	//			}

	//			for (int i = 0; i < room_nums; ++i)
	//			{
	//				auto visibleSize = Director::getInstance()->getVisibleSize();
	//				Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//				auto roomButton = Button::create("room.png", "roomHighlight.png");
	//				//美工
	//				roomButton->setScale9Enabled(true);
	//				roomButton->setTitleText(to_string(room_tag.at(i).asInt()));
	//				roomButton->setTitleFontSize(35);
	//				roomButton->setContentSize(Size(100, 20));
	//				roomButton->setPosition(Vec2(visibleSize.width - 100, 50));

	//				roomButton->addClickEventListener(CC_CALLBACK_1(WaitingScene::clickRoomcallback, this));

	//				roomButton->setTag(i);
	//				this->addChild(roomButton, 2);
	//			}
	//		}

	//	}
	//	Sleep(2 * TIME_LAG);
	//}
	//mtx.unlock();
}

void WaitingScene::menuEnterCallback(Ref* pSender)
{
	//if (WaitingScene::SelectedRoomTags != -1)
	//{
	//	UserDefault* defaults = UserDefault::getInstance();
	//	defaults->setBoolForKey(OWNER, false);
	//	//send room_tag and player of this room message
	//	ValueVector plistdata = GameData::WaitingData(false, WaitingScene::SelectedRoomTags, defaults->getStringForKey(PLAYERNAME));

	//	mtx.lock();
	//	replace = true;

	//	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	//	string sendbuf = enJson->encode_WaitingRoomData();
	//	Client* client = Client::getInstance();
	//	client->send_Cli(sendbuf);

	//	mtx.unlock();
	//Scene changes
	auto scene = RoomScene::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
	//if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	//{
	//	SimpleAudioEngine::getInstance()->playEffect("filename");
	//}
	//}
}

void WaitingScene::createRoomCallback(Ref* pSender)
{
	//mtx.lock();

	//replace = true;

	//mtx.unlock();

	//UserDefault* defaults = UserDefault::getInstance();
	//defaults->setBoolForKey(OWNER, true);
	////send room_tag and player of this room message

	//ValueVector plistdata = GameData::WaitingData(true, WaitingScene::SelectedRoomTags, defaults->getStringForKey(PLAYERNAME));

	//enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	//string sendbuf = enJson->encode_WaitingRoomData();

	//mtx.lock();

	//Client* client = Client::getInstance();
	//client->send_Cli(sendbuf);

	//mtx.unlock();

	auto scene = RoomScene::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
	/*if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
	SimpleAudioEngine::getInstance()->playEffect("filename");
	}*/
}

void WaitingScene::menuReturnCallback(Ref* pSender)
{
	/*mtx.lock();
	replace = true;
	mtx.unlock();*/

	auto scene = HelloWorld::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
	/*if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
	SimpleAudioEngine::getInstance()->playEffect("filename");
	}*/
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
		WaitingScene::SelectedRoomTags = SelectedRoom->getTag();
	}

}

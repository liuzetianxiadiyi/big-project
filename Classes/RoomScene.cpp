#include "RoomScene.h"
#include "SystemHeader.h"
#include "GameData.h"
#include "Client.h"
#include "enJsonParser.h"
#include "WaitingScene.h"
#include "SystemHeader.h"
#include "JsonParser.h"
#include <vector>
#include "GameScene.h"
#include <string>

USING_NS_CC;
using std::string;
using std::vector;

extern mutex mtx;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool RoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto StartGameItem = MenuItemImage::create(
		"StartGameNormal.png",
		"StartGameSelected.png",
		CC_CALLBACK_1(RoomScene::menuDeleteRoomCallback, this)
	);
	StartGameItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2 + 60));
	if (StartGameItem == nullptr ||
		StartGameItem->getContentSize().width <= 0 ||
		StartGameItem->getContentSize().height <= 0)
	{
		problemLoading("'StartGameNormal.png' and 'StartGameSelected.png'");
	}
	else
	{
		StartGameItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2 + 60));
	}
	UserDefault* defaults = UserDefault::getInstance();
	if (!defaults->getBoolForKey(OWNER))
	{
		StartGameItem->setEnabled(true);
	}

	auto DeleteRoomItem = MenuItemImage::create(
		"DeleteRoomNormal.png",
		"DeleteRoomSelected.png",
		CC_CALLBACK_1(RoomScene::menuDeleteRoomCallback, this)
	);
	//DeleteRoomItem->setPosition(125 + visibleSize.width / 2, visibleSize.height / 2);
	if (DeleteRoomItem == nullptr ||
		DeleteRoomItem->getContentSize().width <= 0 ||
		DeleteRoomItem->getContentSize().height <= 0)
	{
		problemLoading("'DeleteRoomNormal.png' and 'DeleteRoomSelected.png'");
	}
	else
	{
		DeleteRoomItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2));
	}
	auto CountryItem = MenuItemImage::create(
		"CountryNormal.png",
		"CountrySelected.png",
		CC_CALLBACK_1(RoomScene::menuDeleteRoomCallback, this)
	);
	CountryItem->setPosition(125 + visibleSize.width / 2-75, visibleSize.height / 2 - 60);
	if (CountryItem == nullptr ||
		CountryItem->getContentSize().width <= 0 ||
		CountryItem->getContentSize().height <= 0)
	{
		problemLoading("'CountryNormal.png' and 'CountrySelected.png'");
	}
	else
	{
		CountryItem->setPosition(Vec2(125 + visibleSize.width / 2, visibleSize.height / 2 - 60));
	}


	auto menu = Menu::create(StartGameItem, DeleteRoomItem, CountryItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto Accont_back = Sprite::create("accont-back.png");

	Accont_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(Accont_back, 0);
	
	//选国家
	//auto china = Button::create("china.png", "china.png", "chinaForbid.png");
	//china->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	//show.push_back(china);
	//china->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	//this->addChild(china, 10);

	////国家button的间隔
	//float country_interval = china->getContentSize().height / 10;

	//auto confirm = Button::create("confirm.png");
	//confirm->setPosition(Vec2(china->getPosition().x + 10 + china->getContentSize().width, china->getPosition().y));
	//confirm->addTouchEventListener(CC_CALLBACK_2(RoomScene::confirmCallBack, this));
	//this->addChild(confirm);

	//auto us = Button::create("america.png", "america.png", "americaForbid.png");
	//us->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - country_interval - china->getContentSize().height));
	//us->setTag(2);
	//hides.push_back(us);
	//us->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	//this->addChild(us, 10);

	//auto japan = Button::create("japan.png", "japan.png", "japanForbid.png");
	//japan->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - country_interval * 2 - china->getContentSize().height * 2));
	//japan->setTag(3);
	//hides.push_back(japan);
	//japan->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	//this->addChild(japan, 10);

	//auto russia = Button::create("russia.png", "russia.png", "russiaForbid.png");
	//russia->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - country_interval * 3 - china->getContentSize().height * 3));
	//hides.push_back(russia);
	//russia->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	//this->addChild(russia, 10);

	////初始隐藏
	//for (auto &country : hides)
	//{
	//	country->runAction(Hide::create());
	//}


	//auto sendsprite = Sprite::create("send.png");
	//if (sendsprite == nullptr)
	//{
	//	problemLoading("'send.png'");
	//}
	//else
	//{
	//	// position the sprite on the center of the screen
	//	sendsprite->setPosition(Vec2(visibleSize.width - 4 * (sendsprite->getContentSize().width), 2 * sendsprite->getContentSize().height - 10));

	//	// add the sprite as a child to this layer
	//	this->addChild(sendsprite, 0);
	//}
	



//let members in the room except owner receive message from server to ensure if their game game is start
//if there is a bug of this function ,you can try create a scene to ensure if it is in onEnterTransitionDidFinish function when the scene is running
//if not, put these code in the function which is runned when the scene is showed

//void RoomScene::recvThread()
//{
//	using namespace RoomMessage;
//	while (true)
//	{
//		Client* client = Client::getInstance();
//		string information = client->recv_Cli();
//		JsonParser* json = JsonParser::createWithC_str(information.c_str());
//		int juggle = json->decode_EnterData();
//		if (juggle == StartGame)
//		{
//			auto scene = GameScene::createScene();	//待定
//			auto reScene = TransitionJumpZoom::create(1.0f, scene);
//			Director::getInstance()->pushScene(reScene);
//			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
//			{
//				SimpleAudioEngine::getInstance()->playEffect("filename");
//			}
//			break;
//		}
//		else if (juggle == DeleteRoom)
//		{
//			auto scene = WaitingScene::createScene();	//待定
//			WaitingScene::replace = false;
//			auto reScene = TransitionJumpZoom::create(1.0f, scene);
//			Director::getInstance()->pushScene(reScene);
//			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
//			{
//				SimpleAudioEngine::getInstance()->playEffect("filename");
//			}
//			break;
//		}
//		else if (juggle == AddMember)
//		{
//			string name = json->getInformation();
//			//create a roomMember sprite
//		}
//	}
//}


//国家的回调函数
return true;

}
void RoomScene::countryCallBack(Ref* pSender, Widget::TouchEventType type)
{

	//Button* button = static_cast<Button*>(pSender);

	//if (type == Widget::TouchEventType::BEGAN)
	//{
	//	log("countryCallBack");
	//	bool hide = false;
	//	for (auto &i : hides)
	//	{
	//		if (i == button)
	//		{
	//			hide = true; break;
	//		}
	//	}
	//	//点击被选中就显示
	//	if (hide == false)
	//	{
	//		log("hide==false");
	//		for (auto i : hides)
	//		{
	//			i->runAction(Show::create());
	//		}
	//	}//点击里面的就改变
	//	else {
	//		log("hide==true");
	//		//交换位置
	//		auto pos1 = button->getPosition();
	//		auto sprite = show[0];
	//		button->setPosition(sprite->getPosition());
	//		sprite->setPosition(pos1);
	//		//交换标记
	//		for (auto i = hides.begin(); i != hides.end(); ++i)
	//		{
	//			if (*i == button)
	//			{
	//				log("%d", i);
	//				log("change flag ");
	//				hides.erase(i);
	//				hides.push_back(show[0]);
	//				break;
	//			}
	//		}

	//		show[0] = button;

	//		//隐藏
	//		for (auto i : hides)
	//		{
	//			i->runAction(Hide::create());
	//		}
	//	}	
	//}
}

void RoomScene::confirmCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		show.front()->setEnabled(false);
	}

}

void RoomScene::CountryButtonCallback(Ref* pSender)
{


}




void RoomScene::menuStartGameCallback(Ref* pSender)
{
	//ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(GameData::toPair(ISSTART, Value(true)))));
	//Client* client = Client::getInstance();
	//enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	//string sendBuf = enJson->encode_EnterGameData();
	//client->send_Cli(sendBuf);

	//WaitingScene::replace = true;
	//auto scene = GameScene::createScene();	//´ý¶¨
	//auto reScene = TransitionJumpZoom::create(1.0f, scene);
	//Director::getInstance()->pushScene(reScene);
	//if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	//{
	//	SimpleAudioEngine::getInstance()->playEffect("filename");
	//}
}

void RoomScene::menuDeleteRoomCallback(Ref* pSender)
{
	/*ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(GameData::toPair(ISSTART, Value(false)))));
	Client* client = Client::getInstance();
	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	string sendBuf = enJson->encode_EnterGameData();
	client->send_Cli(sendBuf);*/

	auto scene = WaitingScene::createScene();	//´ý¶¨
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}


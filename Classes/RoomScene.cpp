#include "RoomScene.h"
#include "SystemHeader.h"
#include "GameData.h"
#include "Client.h"
#include "enJsonParser.h"
#include "WaitingScene.h"
#include "SimpleAudioEngine.h"
#include "time.h"
#include <vector>

USING_NS_CC;
using std::string;
using std::vector;

 string words;
 int i = 204;
 int tag = 1;
 int labelcount = 500;
vector<string> news;
extern mutex mtx;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
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
		CC_CALLBACK_1(RoomScene::menuStartGameCallback, this)
	);
	StartGameItem->setPosition();
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
	DeleteRoomItem->setPosition();
	auto CountryItem = MenuItemImage::create(
		"CountryNormal.png",
		"CountrySelected.png",
		CC_CALLBACK_1(RoomScene::CountryButtonCallback, this)
	);
	CountryItem->setPosition();

	auto menu = Menu::create(StartGameItem, DeleteRoomItem, CountryItem);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Sprite * Accont_back = Sprite::create("Room-back.png");

	Accont_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(Accont_back, 0);
	
	//选国家
	auto china = Button::create("china.png", "china.png", "chinaForbid.png");
	china->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	show.push_back(china);
	china->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(china, 10);

	//国家button的间隔
	float country_interval = china->getContentSize().height/10;
	
	auto confirm = Button::create("confirm.png");
	confirm->setPosition(Vec2(china->getPosition().x+10+china->getContentSize().width,china->getPosition().y));
	confirm->addTouchEventListener(CC_CALLBACK_2(RoomScene::confirmCallBack, this));
	this->addChild(confirm);
	
	auto us = Button::create("america.png","america.png","americaForbid.png");
	us->setPosition(Vec2(visibleSize.width / 2.0f , visibleSize.height / 2.0f - country_interval - china->getContentSize().height));
	us->setTag(2);
	hides.push_back(us);
	us->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(us, 10);

	auto japan = Button::create("japan.png", "japan.png", "japanForbid.png");
	japan->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - country_interval * 2 - china->getContentSize().height * 2));
	japan->setTag(3);
	hides.push_back(japan);
	japan->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(japan, 10);

	auto russia = Button::create("russia.png", "russia.png", "russiaForbid.png");
	russia->setPosition(Vec2(visibleSize.width / 2.0f , visibleSize.height / 2.0f - country_interval * 3 - china->getContentSize().height * 3));
	hides.push_back(russia);
	russia->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(russia, 10);

	//初始隐藏
	for (auto &country : hides)
	{		
		country->runAction(Hide::create());		
	}
	
	
	auto sendsprite = Sprite::create("send.png");
	if (sendsprite == nullptr)
	{
		problemLoading("'send.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sendsprite->setPosition(Vec2(visibleSize.width - 4 * (sendsprite->getContentSize().width), 2 * sendsprite->getContentSize().height-10));

		// add the sprite as a child to this layer
		this->addChild(sendsprite, 0);
	}


      //聊天框
	auto MessageItem = MenuItemImage::create(
		"pastmessage.png",
		"pastmessage.png",
		CC_CALLBACK_1(HelloWorld::messageCallback, this)
	);

	if (MessageItem == nullptr ||
		MessageItem->getContentSize().width <= 0 ||
		MessageItem->getContentSize().height <= 0)
	{
		problemLoading("'pastmessage.png' and pastmessage.png'");
	}
	else
	{
		float x = visibleSize.width - 2*(MessageItem->getContentSize().width );
		float y = 2* MessageItem->getContentSize().height-50 ;
		MessageItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu2 = Menu::create(MessageItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

	auto pEditBox_name = EditBox::create(CCSizeMake(250,50), Scale9Sprite::create("text2.png"));
	pEditBox_name->setPosition(ccp(visibleSize.width *1/ 3, visibleSize.height * 1/ 5));
	pEditBox_name->setFontColor(Color3B(0, 0, 0));//设置字体颜色  
	pEditBox_name->setFont("Arial", 20);
	pEditBox_name->setPlaceHolder("Input: ");//设置预置文本    
	pEditBox_name->setMaxLength(160);//设置最大长度    
	pEditBox_name->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);//可以输入任何，但是不包括换行   
	pEditBox_name->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位    
	pEditBox_name->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型    
	pEditBox_name->setDelegate(this);//当前类继承CCEditBoxDelegate类    
	pEditBox_name->setTag(101);
	this->addChild(pEditBox_name,2);


	return true;
}

void RoomScene::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}

void RoomScene::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
	
}

//let members in the room except owner receive message from server to ensure if their game game is start
//if there is a bug of this function ,you can try create a scene to ensure if it is in onEnterTransitionDidFinish function when the scene is running
//if not, put these code in the function which is runned when the scene is showed
void RoomScene::onEnterTransitionDidFinish()
{
	UserDefault* defaults = UserDefault::getInstance();
	if (!defaults->getBoolForKey(OWNER))
	{
		Client* client = Client::getInstance();
		string information = client->recv_Cli();
		JsonParser* json = JsonParser::createWithC_str(information.c_str());
		if (json->decode_EnterData())
		{
			auto scene = GameScene::createScene();	//待定
			auto reScene = TransitionJumpZoom::create(1.0f, scene);
			Director::getInstance()->pushScene(reScene);
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
			{
				SimpleAudioEngine::getInstance()->playEffect("filename");
			}
		}
		else
		{
			auto scene = WaitingScene::createScene();	//待定
			WaitingScene::replace = false;
			auto reScene = TransitionJumpZoom::create(1.0f, scene);
			Director::getInstance()->pushScene(reScene);
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
			{
				SimpleAudioEngine::getInstance()->playEffect("filename");
			}
		}
	}
}

//聊天框历史消息回调函数
void RoomScene::messageCallback(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("pastnews.png");
	sprite->setTag(498);
	if (sprite == nullptr)
	{
		problemLoading("'pastnews.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 3 +origin.x, visibleSize.height /2 + origin.y+40));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::messageCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width/2 +closeItem->getContentSize().width / 2;
		float y = origin.y + visibleSize.height- closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1,497);


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
				problemLoading("'fonts/Marker Felt.ttf'");
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
			++tag;
		
	

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
	slider->addEventListener(CC_CALLBACK_2(RoomScene::onChangedSlider2, this));
	this->addChild(slider, 1,499);
	
}
//聊天框发送信息
void RoomScene::editBoxReturn(EditBox *editBox)
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
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(ccp(visibleSize.width * 1 / 5, visibleSize.height *  5/6  - (label->getContentSize().height*(i % 12))));
			// add the label as a child to this layer
			this->addChild(label, 1,i);
			this->removeChildByTag(i - 12);
			i = i + 1;
		}
		auto label2 = Label::createWithTTF(asctime(time1), "fonts/Marker Felt.ttf", 24);
		if (label2 == nullptr)
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label2->setPosition(ccp(visibleSize.width * 2 / 5,( visibleSize.height * 5 / 6 +2*(label->getContentSize().height) -(label->getContentSize().height*(i % 12)))-6));
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

//国家的回调函数
void RoomScene::countryCallBack(Ref* pSender, Widget::TouchEventType type)
{
	
	Button* button = static_cast<Button*>(pSender);
	
	if (type == Widget::TouchEventType::BEGAN)
	{
		log("countryCallBack");
		bool hide = false;
		for (auto &i : hides)
		{
			if (i == button)
			{
				hide = true; break;
			}
		}
		//点击被选中就显示
		if (hide == false)
		{
			log("hide==false");
			for (auto i :hides)
			{				
				i->runAction(Show::create());
			}
		}
		//点击里面的就改变
		else
		{
			log("hide==true");
			//交换位置
			auto pos1 = button->getPosition();			
			auto sprite = show[0];
			button->setPosition(sprite->getPosition());
			sprite->setPosition(pos1);

			//交换标记
			for (auto i =hides.begin();i!=hides.end();++i)
			{
				if (*i == button)
				{
					log("%d", i);
					log("change flag ");
					hides.erase(i);
					hides.push_back(show[0]);
					break;
				}
			}
			
			show[0]=button;

			//隐藏
			for (auto i :hides)
			{
				i->runAction(Hide::create());
			}
		}
	}			
}

void RoomScene::confirmCallBack(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		show.front()->setEnabled(false);
	}
		
}

void RoomScene::editBoxTextChanged(EditBox *editBox, const std::string &text)
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

void RoomScene::onChangedSlider2(Ref* pSender, Slider::EventType type)
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent() * 5;
		for (int m = 500; m <labelcount; m++)
		{
			auto label1 = getChildByTag(m);
			label1->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 100-30*(m-500) + percent
			)));
		
	}

void RoomScene::menuStartGameCallback(Ref* pSender)
{
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(GameData::toPair(ISSTART,Value(true)))));
	Client* client = Client::getInstance();
	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	string sendBuf = enJson->encode_EnterGameData();
	client->send_Cli(sendBuf);

	auto scene = GameScene::createScene();	//´ý¶¨
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

void RoomScene::menuDeleteRoomCallback(Ref* pSender)
{
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(GameData::toPair(ISSTART, Value(false)))));
	Client* client = Client::getInstance();
	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	string sendBuf = enJson->encode_EnterGameData();
	client->send_Cli(sendBuf);

	auto scene = WaitingScene::createScene();	//´ý¶¨
	WaitingScene::replace = false;
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

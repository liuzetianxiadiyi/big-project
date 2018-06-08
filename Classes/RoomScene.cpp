#include "RoomScene.h"
#include "SystemHeader.h"
#include "GameData.h"
#include "Client.h"
#include "enJsonParser.h"
#include "WaitingScene.h"
#include <vector>
#include <iostream>

using std::string;
using std::vector;

 string words;
 int i = 204;
 int tag = 1;
vector<string> news;

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

void RoomScene::onEnter()
{
	Layer::onEnter();
	//
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(RoomScene::touchBegin, this);
	listener->onTouchMoved = CC_CALLBACK_2(RoomScene::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(RoomScene::touchEnded, this);

	auto eventdis = Director::getInstance()->getEventDispatcher();
	eventdis->addEventListenerWithSceneGraphPriority(listener, getChildByTag(1));
	eventdis->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(2));
	eventdis->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(3));
	eventdis->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(4));

}

void RoomScene::onExit()
{
	Layer::onExit();

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
	slider->setTag(5);
	slider->setPosition(Vec2(visibleSize.width / 2.0f + 60, visibleSize.height / 2.0f));
	slider->addEventListener(CC_CALLBACK_2(RoomScene::onChangedSlider, this));
	
	this->addChild(slider, 10);

	auto china = Sprite::create("china.png");
	china->setPosition(Vec2(500, 500));
	china->setTag(1);
	this->addChild(china, 10);

	auto us = Sprite::create("us.png");
	us->setPosition(Vec2(500, 500 - 30 - china->getContentSize().height));
	us->setTag(2);
	this->addChild(us, 10);

	auto c1 = Sprite::create("china.png");
	c1->setPosition(Vec2(500, 500 - 30 * 2 - china->getContentSize().height * 2));
	c1->setTag(3);
	this->addChild(c1, 10);

	auto c2 = Sprite::create("us.png");
	c2->setPosition(Vec2(500, 500 - 30 * 3 - china->getContentSize().height * 3));
	c2->setTag(4);
	this->addChild(c2, 10);

	//初始隐藏
	for (auto i = hides.begin(); i != hides.end(); ++i)
	{
		auto sprite = getChildByTag(*i);
		sprite->runAction(Hide::create());
	}

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


	return true;
}

void RoomScene::messageCallback(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("pastnews.png");
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

	for (int j = i; j >= i - 12; j--)
	{
		this->removeChildByTag(j);
	}
	int count = 0;
	int labelcount = 500;
	if (tag == 1)
	{
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
			++tag;
		}
	}

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
	this->addChild(slider, 1);
	
}
void RoomScene::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}

void RoomScene::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
	
}

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

		time1 = localtime(&now);      //microseconds: 
		int year = time1->tm_year + 1900;
		log("year = %d", year);     
		asctime(time1);
		char date1[32] = { 0 };
		sprintf(date1, "%d %02d %02d", (int)time1->tm_year + 1900, (int)time1->tm_mon + 1, (int)time1->tm_mday);
		log("%s", date1);      

		char date2[50] = { 0 };
		sprintf(date2, "%02d %02d %02d", (int)time1->tm_hour, (int)time1->tm_min, (int)time1->tm_sec);
		log("%s", date2);   
		
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
			label->setPosition(ccp(visibleSize.width * 1 / 5, visibleSize.height *  5/6  - (2)*(label->getContentSize().height*(i % 6))));
			// add the label as a child to this layer
			this->addChild(label, 1,i);
			this->removeChildByTag(i - 6);
		}
		
		auto label2 = Label::createWithTTF(asctime(time1), "fonts/Marker Felt.ttf", 24);
		if (label2 == nullptr)
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label2->setPosition(ccp(visibleSize.width * 2 / 5,( visibleSize.height * 5 / 6 +label->getContentSize().height -(label2->getContentSize().height*(i % 6)))-6));
			// add the label as a child to this layer
			this->addChild(label2, 1, i);
			this->removeChildByTag(i - 6);
		}
		editBox->setText("");
		i = i + 1;
	}
	
	if (editBox->getTag() == 102)
	{
		editBox->setText("you recieved a letter");
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

//
bool RoomScene::touchBegin(Touch* touch, Event* event)
{
	//获取被点击的国家
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInnode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	log("choose%d", target->getTag());
	bool hide = false;
	for (auto i = hides.begin(); i != hides.end(); ++i)
	{
		if (*i == target->getTag())
		{
			hide = true; break;
		}
	}
	log("%d", hide);

	//点击被选中的国家就显示其他国家
	if (hide == false)
	{
		for (auto i = hides.begin(); i != hides.end(); ++i)
		{
			auto sprite = getChildByTag(*i);
			sprite->runAction(Show::create());
		}
	}
	//点击滑块里的国家
	else
	{
		//交换两个国家的位置
		auto pos1 = target->getPosition();
		target->setPosition(chosen_position);
		auto sprite = getChildByTag(show[0]);
		sprite->setPosition(pos1);

		//交换两个国家的标记
		for (auto i = hides.begin(); i != hides.end(); ++i)
		{
			if (*i == target->getTag())
			{
				*i = show.front();
				break;
			}
		}
		show.front() = target->getTag();

		//隐藏滑块和国家
		for (auto i = hides.begin(); i != hides.end(); ++i)
		{
			auto sprite = getChildByTag(*i);
			sprite->runAction(Hide::create());
		}

	}
	return true;
}

void RoomScene::touchMoved(Touch* touch, Event* event)
{}

void RoomScene::touchEnded(Touch* touch, Event* event)
{}

//Slider滑动事件回调函数
void RoomScene::onChangedSlider(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent() * 0.5;

		//获取滑块里的国家进行移动
		
		for (auto i = hides.begin(),j=0; i != hides.end()-1; ++i,++j)
		{
			auto sprite = getChildByTag(*i);
			sprite->runAction(MoveTo::create(0.1,Vec2(sprite->getPosition().x, sprite->getPosition().y + percent)));
		}

	}
}

void RoomScene::onChangedSlider2(Ref* pSender, Slider::EventType type)
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent() * 2.5;
		for (int m = 500; m <= 511; m++)
		{
			auto label1 = getChildByTag(m);
			label1->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 100-30*(m-500) + percent
			)));
		}
	}
}

void RoomScene::menuStartGameCallback(Ref* pSender)
{
	ValueVector plistdata = GameData::toValueVector(Value(GameData::toValueMap(GameData::toPair(ISSTART,Value(true)))));
	Client* client = Client::getInstance();
	enJsonParser* enJson = enJsonParser::createWithArray(plistdata);
	string sendBuf = enJson->encode_EnterGameData();
	client->send_Cli(sendBuf);

	auto scene = ::createScene();	//´ý¶¨
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
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename");
	}
}

#include "RoomScene.h"
#include "SystemHeader.h"
#include "GameData.h"
#include "Client.h"
#include "enJsonParser.h"
#include "WaitingScene.h"

using std::string;

 string words;
 int i = 204;

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
	auto china = Button::create("china.png");
	china->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	show.push_back(china);
	china->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(china, 10);

	//国家button的间隔
	float country_interval = china->getContentSize().height/10;

	auto us = Button::create("america.png");
	us->setPosition(Vec2(visibleSize.width / 2.0f , visibleSize.height / 2.0f - country_interval - china->getContentSize().height));
	us->setTag(2);
	hides.push_back(us);
	us->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(us, 10);

	auto japan = Button::create("japan.png");
	japan->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - country_interval * 2 - china->getContentSize().height * 2));
	japan->setTag(3);
	hides.push_back(japan);
	japan->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(japan, 10);

	auto russia = Button::create("russia.png");
	russia->setPosition(Vec2(visibleSize.width / 2.0f , visibleSize.height / 2.0f - country_interval * 3 - china->getContentSize().height * 3));
	hides.push_back(russia);
	russia->addTouchEventListener(CC_CALLBACK_2(RoomScene::countryCallBack, this));
	this->addChild(russia, 10);

	//初始隐藏
	for (auto &country : hides)
	{		
		country->runAction(Hide::create());		
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

void RoomScene::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
	auto editbox = (EditBox*)editBox;

	if (editBox->getTag() == 101)
	{
		
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
			label->setPosition(ccp(visibleSize.width * 1 / 5, visibleSize.height *  5/6  - label->getContentSize().height*(i % 6)));

			// add the label as a child to this layer
			this->addChild(label, 1,i);
			this->removeChildByTag(i - 6);
		}
		editBox->setText("");
		++i;
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
		//点击滑块里的就改变
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

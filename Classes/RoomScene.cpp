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

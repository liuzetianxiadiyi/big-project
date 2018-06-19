#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define NUMBER_BUTTONS 5
#define BUTTON_WIDTH 60

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	
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

	slider->setPosition(Vec2(visibleSize.width / 2.0f+60, visibleSize.height / 2.0f));
	slider->addEventListener(CC_CALLBACK_2(HelloWorld::onChangedSlider, this));
	this->addChild(slider,1);

	auto china = Sprite::create("china.png");
	china->setPosition(Vec2(500, 500));
	china->setTag(1);
	this->addChild(china, 0);

	auto us = Sprite::create("us.png");
	us->setPosition(Vec2(500, 500- 30-china->getContentSize().height));
	us->setTag(2);
	this->addChild(us, 0);
	
	auto c1 = Sprite::create("china.png");
	c1->setPosition(Vec2(500, 500 - 30*2-china->getContentSize().height *2));
	c1->setTag(3);
	this->addChild(c1, 0);
	
	auto c2 = Sprite::create("us.png");
	c2->setPosition(Vec2(500, 500 - 30*3- china->getContentSize().height * 3));
	c2->setTag(4);
	this->addChild(c2, 0);
	


	return true;
}

//Slider滑动事件回调函数
void HelloWorld::onChangedSlider(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent() * 2.5;
		auto china = getChildByTag(1);
		auto us = getChildByTag(2);
		auto c1=getChildByTag(3);
		auto c2 = getChildByTag(4);
		c1->runAction(MoveTo::create(0.5, Vec2(500, 500 - 30*2 - china->getContentSize().height*2 + percent)));
		c2->runAction(MoveTo::create(0.5, Vec2(500, 500 - 30*3 - china->getContentSize().height *3 + percent)));
		us->runAction(MoveTo::create(0.5, Vec2(500, 500 - 30 - china->getContentSize().height + percent)));
		china->runAction(MoveTo::create(0.5,Vec2(500,500+percent)));
		

	}
}

#include "SettingScene.h"
#include "curl/curl.h"
#pragma comment(lib,"libcurl_imp.lib")

using namespace CocosDenshion;

Scene* Setting::createScene()
{
	auto scene = Scene::create();
	auto layer = Setting::create();
	scene->addChild(layer);
	return scene;
}

bool Setting::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置Setting界面的背景
	Sprite * setting_back = Sprite::create("setting_back.png");
	setting_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(setting_back, 1);

	//设置音乐和音效

	//音效设置按键
	auto soundOnMenuItem = MenuItemImage::create(
		"on.png",
		"on.png");
	auto soundOffMenuItem = MenuItemImage::create(
		"off.png",
		"off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(100 + visibleSize.width / 2, visibleSize.height / 2 - 50)));

	//音乐设置按键
	auto musicOnMenuItem = MenuItemImage::create(
		"on.png",
		"on.png");
	auto musicOffMenuItem = MenuItemImage::create(
		"off.png",
		"off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(100 + visibleSize.width / 2, visibleSize.height / 2)));

	//确认按键
	auto okMenuItem = MenuItemImage::create(
		"ok-down.png",
		"ok-up.png",
		CC_CALLBACK_1(Setting::menuOkCallback, this));
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75)));

	Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn, 2);

	return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	
}

void Setting::menuMusicToggleCallback(Ref* pSender)
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;

	if (musicToggleMenuItem->getSelectedIndex() == 1) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		/*isEffect = false;*/
	}
	else {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		/*isEffect = true;*/
	}
}

void Setting::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld onEnterTransitionDidFinish");
	/*isEffect = true;*/
}

void Setting::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
}

void Setting::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("HelloWorld onExitTransitionDidStart");
}

void Setting::cleanup()
{
	Layer::cleanup();
	log("HelloWorld cleanup");
}





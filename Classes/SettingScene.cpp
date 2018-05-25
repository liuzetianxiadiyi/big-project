#include "SettingScene.h"
#include "curl/curl.h"
#pragma comment(lib,"libcurl_imp.lib")

using namespace CocosDenshion;
Scene* Setting::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
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

	Sprite * setting_back = Sprite::create("setting-back.png");

	setting_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(setting_back, 1);

	//??
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
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 220)));

	//??
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
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(818, 362)));

	//Ok??
	auto okMenuItem = MenuItemImage::create(
		"ok-down.png",
		"ok-up.png",
		CC_CALLBACK_1(Setting::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));

	Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY))
	{
		musicToggleMenuItem->setSelectedIndex(0);
	}
	else
	{
		musicToggleMenuItem->setSelectedIndex(1);
	}

	if (defaults->getBoolForKey(SOUND_KEY))
	{
		soundToggleMenuItem->setSelectedIndex(0);
	}
	else
	{
		soundToggleMenuItem->setSelectedIndex(1);
	}
	return true;
}

void Setting::menuOkCallback(Ref* pSender)
{
	auto defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename.wav");
	}
	Director::getInstance()->popScene();
}

void Setting::menuSoundToggleCallback(Ref* pSender)
{
	auto soundToggleMenuItem = dynamic_cast<MenuItemToggle *> (pSender);

	UserDefault * defaults = UserDefault::getInstance();

	if (defaults->getBoolForKey(SOUND_KEY))
	{
		defaults->setBoolForKey(SOUND_KEY, false);
	}
	else
	{
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect("filename.wav");
	}
}
void Setting::menuMusicToggleCallback(Ref* pSender)
{
	auto musicMenuToggleItem = dynamic_cast<MenuItemToggle *> (pSender);

	UserDefault * defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename.wav");
	}
	if (defaults->getBoolForKey(MUSIC_KEY))
	{
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("filename.mp3");
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
	//²¥·Å
	SimpleAudioEngine::getInstance()->playBackgroundMusic("filename.mp3", true);
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
	//Í£Ö¹
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("filename.mp3");
}
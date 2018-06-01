#include"GamePlay.h"
USING_NS_CC;

Scene* GamePlay::createScene()
{
	auto scene = Scene::create();
	auto layer = GamePlay::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlay::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//贴图的纹理图片宽高必须是2的n次幂，128x128
	auto bg = Sprite::create("BackgroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	//贴图的纹理参数，水平重复平铺，垂直重复平铺
	Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	bg->getTexture()->setTexParameters(tp);
	bg->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg, 0);

	//以后此处精灵缓存优化

	auto soilder = Sprite::create("soilder.png");
	// position the sprite on the center of the screen
	soilder->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(soilder, 10, soilder_Tag);

	auto tank = Sprite::create("tank.png");
	// position the sprite on the center of the screen
	tank->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(tank, 10, tank_Tag);

	auto base = Sprite::create("base.png");
	// position the sprite on the center of the screen
	base->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(base, 0);

	auto barracks = Sprite::create("barracks.png");
	// position the sprite on the center of the screen
	barracks->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(barracks, 0);

	auto army = Sprite::create("army.png");
	// position the sprite on the center of the screen
	army->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(army, 10, army_Tag);

	auto building = Sprite::create("building.png");
	// position the sprite on the center of the screen
	barracks->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	// add the sprite as a child to this layer
	this->addChild(building, 10, building_Tag);

	auto ContinueItem = MenuItemImage::create(
		"ContinueItemNormal.png",
		"ContinueItemSelected.png",
		CC_CALLBACK_1(GamePlay::menuContinueCallback, this)
	);
	
	ContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto SettingItem = MenuItemImage::create(
		"SettingNormal.png",
		"SettingSelect.png",
		CC_CALLBACK_1(GamePlay::menuSettingCallback, this)
	);
	SettingItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 20));
	auto ExitItem = MenuItemImage::create(
		"ExitNormal.png",
		"ExitSelected.png",
		CC_CALLBACK_1(GamePlay::menuExitCallback, this)
	);
	ExitItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
	auto GiveUpItem = MenuItemImage::create(
		"GiveUpItemNormal.png",
		"GiveUpItemSelected.png",
		CC_CALLBACK_1(GamePlay::menuContinueCallback, this)
	);	
	GiveUpItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(ContinueItem, GiveUpItem, SettingItem, ExitItem, NULL);
	//垂直对齐
	menu->alignItemsVertically();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void GamePlay::onEnter()
{
	Layer::onEnter();
	log("GamePlay onEnter");
}

void GamePlay::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GamePlay onEnterTransitionDidFinish");
	
	// 创建一个事件监听器 OneByOne 为单点触摸
	auto listener = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener->setSwallowTouches(true);
	// onTouchBegan 事件回调函数
	listener->onTouchBegan = CC_CALLBACK_2(GamePlay::touchBegan, this);
	// onTouchMoved 事件回调函数
	listener->onTouchMoved = CC_CALLBACK_2(GamePlay::touchMoved, this);
	// onTouchEnded 事件回调函数
	listener->onTouchEnded = CC_CALLBACK_2(GamePlay::touchEnded, this);

	// 注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(army_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(building_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(soilder_Tag));

}


bool GamePlay::touchBegan(Touch* touch, Event* event)
{
	// 获取事件所绑定的 target 
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	// 获取当前点击点所在相对按钮的位置坐标
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite x = %f, y = %f ", locationInNode.x, locationInNode.y);
		log("sprite tag = %d", target->getTag());
		target->runAction(ScaleBy::create(0.06f, 1.06f));
		return true;
	}
	return false;
}
//建筑才需要移动,兵种不需要
//
void GamePlay::touchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	// 移动当前按钮精灵的坐标位置
	target->setPosition(target->getPosition() + touch->getDelta());
}

void GamePlay::touchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	log("sprite onTouchesEnded.. ");

	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite x = %f, y = %f ", locationInNode.x, locationInNode.y);
		log("sprite tag = %d", target->getTag());
		target->runAction(ScaleTo::create(0.06f, 1.0f));
	}
}

void GamePlay::onExit()
{
	Layer::onExit();
	log("GamePlay onExit");
}

void GamePlay::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("GamePlay onExitTransitionDidStart");
}

void GamePlay::cleanup()
{
	Layer::cleanup();
	log("GamePlay cleanup");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	
}

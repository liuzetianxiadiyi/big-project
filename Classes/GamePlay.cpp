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

	//��ͼ������ͼƬ��߱�����2��n���ݣ�128x128
	auto bg = Sprite::create("BackgroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	//��ͼ�����������ˮƽ�ظ�ƽ�̣���ֱ�ظ�ƽ��
	Texture2D::TexParams tp = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	bg->getTexture()->setTexParameters(tp);
	bg->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg, 0);

	//�Ժ�˴����黺���Ż�

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
	//��ֱ����
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
	
	// ����һ���¼������� OneByOne Ϊ���㴥��
	auto listener = EventListenerTouchOneByOne::create();
	// �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
	listener->setSwallowTouches(true);
	// onTouchBegan �¼��ص�����
	listener->onTouchBegan = CC_CALLBACK_2(GamePlay::touchBegan, this);
	// onTouchMoved �¼��ص�����
	listener->onTouchMoved = CC_CALLBACK_2(GamePlay::touchMoved, this);
	// onTouchEnded �¼��ص�����
	listener->onTouchEnded = CC_CALLBACK_2(GamePlay::touchEnded, this);

	// ע�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(army_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(building_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), getChildByTag(soilder_Tag));

}


bool GamePlay::touchBegan(Touch* touch, Event* event)
{
	// ��ȡ�¼����󶨵� target 
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	// ��ȡ��ǰ�����������԰�ť��λ������
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// �����Χ�жϼ��
	if (rect.containsPoint(locationInNode))
	{
		log("sprite x = %f, y = %f ", locationInNode.x, locationInNode.y);
		log("sprite tag = %d", target->getTag());
		target->runAction(ScaleBy::create(0.06f, 1.06f));
		return true;
	}
	return false;
}
//��������Ҫ�ƶ�,���ֲ���Ҫ
//
void GamePlay::touchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	// �ƶ���ǰ��ť���������λ��
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
	// �����Χ�жϼ��
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

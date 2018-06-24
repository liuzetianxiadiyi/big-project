#include "AccontScene.h"
#include "SystemHeader.h"
//#include "Client.h"
//#include "WaitingScene.h"
#include "Information.h"
//#include "enJsonParser.h"
//#include "GameData.h"
////////////////////////////
#include"GameScene.h"
#include <iostream>

using std::string;

//Information information;

Scene* AccontScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AccontScene::create();
	scene->addChild(layer);
	return scene;
}

bool AccontScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite * Accont_back = Sprite::create("accont-back.png");

	Accont_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(Accont_back, 1);

	//账号框
	auto editbox = EditBox::create(Size(200, 35), Scale9Sprite::create("editbox.png"));
	editbox->setAnchorPoint(Point(0, 0));
	editbox->setPosition(Point(visibleSize.width *0.3, visibleSize.height*0.55));
	editbox->setPlaceHolder("name:");//占位字符  
	editbox->setMaxLength(8000);
	editbox->setFontColor(Color3B::BLACK);//设置输入字体的颜色  
	editbox->setText("player");
	editbox->setTag(1);
	this->addChild(editbox, 2);

	//创建Button
	auto button = Button::create("button.png", "buttonHighlight.png");
	
	button->setScale9Enabled(true);
	button->setTitleText("OK");
	button->setTitleFontSize(35);
	button->setContentSize(Size(100,20));
	button->setPosition(Vec2(visibleSize.width - 100, 50));

	//设置button的监听器
	button->addClickEventListener(CC_CALLBACK_1(AccontScene::buttonOkCallback, this));

	this->addChild(button, 2);
}

void AccontScene::buttonOkCallback(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("filename.wav");
	}
	auto editbox = dynamic_cast<EditBox*>(this->getChildByTag(1));

	string text = string(editbox->getText());
	int len = text.length();

	auto scene = GameScene::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
	//if (len == 0)
	//{
	//	this->removeChildByTag(3);
	//	auto label1 = Label::createWithSystemFont("名字不可为空！", "Arial", 15);
	//	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height / 3));					//这种位置的东西麻烦美工量一下，谢谢
	//	label1->setTag(2);
	//	label1->addChild(label1, 2);
	//	this->addChild(label1, 3);
	//}
	//else if (len < 4)
	//{
	//	this->removeChildByTag(2);
	//	auto label2 = Label::createWithSystemFont("至少需要4个字符！", "Arial", 15);
	//	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height /3));					
	//	label2->setTag(3);
	//	this->addChild(label2, 3);
	//}
	//else
	//{
	//	/*UserDefault * defaults = UserDefault::getInstance();
	//	defaults->setStringForKey(PLAYERNAME, text);
	//	auto scene = WaitingScene::createScene();
	//	auto reScene = TransitionJumpZoom::create(1.0f, scene);
	//	Director::getInstance()->replaceScene(reScene);*/
	//}
}
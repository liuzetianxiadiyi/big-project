#ifndef __ACCONT_H__
#define __ACCONT_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui/CocosGUI.h"
#include <ctime>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class AccontScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	//声明周期函数
	virtual bool init();

	void buttonOkCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(AccontScene);
};

#endif
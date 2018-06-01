#ifndef __WAITINGSCENE_H_
#define __WAITINGSCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::ui;

class WaitingScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	static int room_nums;
	static int SelectedRoomTag;
	static bool replace;	//to jugde if WaitingScene is replaced

	bool init();

	void menuEnterCallback(cocos2d::Ref* pSender);
	void createRoomCallback(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);

	void clickRoomcallback(cocos2d::Ref* pSende);
	
//Slider-return back func
	void onChangedSlider(Ref* pSender, Slider::EventType type);

	void roomDataThread();

	CREATE_FUNC(WaitingScene);
};
#endif // !WaitingScene

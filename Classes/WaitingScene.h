#ifndef __WAITINGSCENE_H_
#define __WAITINGSCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>


USING_NS_CC;
using namespace cocos2d::ui;

class WaitingScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	int room_nums;
	static int SelectedRoomTag;
	static bool replace;	//to jugde if WaitingScene is replaced

	bool init();
	void onEnterTransitionDidFinish();

	void menuEnterCallback(cocos2d::Ref* pSender);
	void createRoomCallback(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);

	void clickRoomcallback(cocos2d::Ref* pSende);
	
//Slider-return back func
	void onChangedSlider(Ref* pSender, Slider::EventType type);

	void roomDataThread();

	CREATE_FUNC(WaitingScene);
private:
	int SelectedRoomTags = -1;
};
#endif // !WaitingScene

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Military.h"
#include "Construction.h"
#include "FindWay.h"

#include"ui/CocosGUI.h"
#include"cocos-ext.h"

#include<vector>
#include <queue>
#include <string>
#include "Client.h"
#include <mutex>

using std::string;
using namespace std;
using namespace cocos2d::ui;
USING_NS_CC;
USING_NS_CC_EXT;

class GameScene :public cocos2d::Layer, EditBoxDelegate
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	vector<Military*> unselectedMilitary;
	vector<Military*> selectedMilitary;
	vector<Construction*>  MyConstructions;
	Vec2 ViewPosition;
	const int ViewChangeSpeed = 32;	//待调整
	vector<MyTile> closeTile;
	vector<MyTile> openTile;
	//string sendBuf;
	string recvbuf;
	static Client* client;
	mutex mtx;

	Vec2 BeginLocation;
	Sprite* smap;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(Vec2 position);

	virtual bool onMouseDown(cocos2d::Event * event);
	virtual void onMouseUp(cocos2d::Event* event);
	virtual void onMouseMove(cocos2d::Event* event);
	virtual void onMouseScroll(cocos2d::Event* event);
	void ButtonSettingCallback(Ref* pSender);
	virtual void onKeyPress(EventKeyboard::KeyCode keyCode, Event* event);

	void messageCallback(cocos2d::Ref* pSender);
	void messageCloseCallback(cocos2d::Ref* pSender);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
	void onChangedSlider2(Ref* pSender, Slider::EventType type);

	//friend class Tile;
	vector<Position> FindWay(Position start, Position goal);
	bool ColsCheck(Vec2 pos);
	bool ConstructionCheck(Vec2 pos);

	void SendDataThread();
	void RecvDataThread();
	void updateMilitary(ValueVector& valuevector, int type);
	void updateConstruction(ValueVector& valuevector, int type);

	CREATE_FUNC(GameScene);
};

#endif // !__GAMESCENE_H__

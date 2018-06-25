#include "TestScene.h"
#include "Client.h"
#include <string>
#include "JsonParser.h"
#include "GameData.h"

Scene* TestScene::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}

bool TestScene::init()
{
	Client* client = Client::getInstance();
	string information = client->recv_Cli();
	log("%s", information);
	JsonParser* Json = JsonParser::createWithC_str(information.c_str());
	Json->decode_WaitingData();

	ValueMap temp = Json->getList()[0].asValueMap()[SWAITINGSCENEDATA].asValueMap();
	log("AddRoom:%d", temp[ADDROOM].asInt());
	log("Deleted:%d", temp[DELETED].asBool());
	client->send_Cli("");
	return true;
}
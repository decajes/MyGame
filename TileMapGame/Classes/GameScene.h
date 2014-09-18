#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "OperateLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);
	CREATE_FUNC(GameScene);
	bool init();

	//cocos2d::TMXTiledMap *m_tileMap;
	//cocos2d::TMXLayer *_background;
private:
	GameLayer *gameLayer;
	OperateLayer *operateLayer;
	void preLoadResource();
};


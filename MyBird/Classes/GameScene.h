#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "TouchLayer.h"
#include "ScoreLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);
	CREATE_FUNC(GameScene);
	bool init();

private:
	//void preload();

	BackgroundLayer* backgroundLayer;
    GameLayer* gameLayer;
	TouchLayer* touchLayer;
	ScoreLayer* scoreLayer;
};


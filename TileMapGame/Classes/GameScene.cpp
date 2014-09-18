#include "GameScene.h"
USING_NS_CC;

GameScene::GameScene(void)
{
	
}


GameScene::~GameScene(void)
{

}

bool GameScene::init()
{
	this->preLoadResource();
	
	gameLayer = GameLayer::create();
	this->addChild(gameLayer);

	operateLayer = OperateLayer::create();
	this->addChild(operateLayer, 1);
	operateLayer->setHero(gameLayer->getHero());

	return true;
}

void GameScene::preLoadResource()
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
    
}

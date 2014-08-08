#include "GameScene.h"
USING_NS_CC;

GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

//void GameScene::preload()
//{
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/game.plist");
//
//	//prelaod the bird animation
//	auto birdAnimation = Animation::create();
//	birdAnimation->setDelayPerUnit(0.2f);
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_0.png"));
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_1.png"));
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_2.png"));
//	AnimationCache::getInstance()->addAnimation(birdAnimation,"birdAnimation");
//}

bool GameScene::init()
{
   do
   {
	   /*initialize the scene with a physical world*/
	   if(!Scene::initWithPhysics())
	   {
		   break;
	   }
	   //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	   this->getPhysicsWorld()->setGravity(Vect(0, -600));
	  
	   /* -----------------------------    */

	   //preload();//after finish the startLayer ,remove
	   
	   backgroundLayer = BackgroundLayer::create();
	   this->addChild(backgroundLayer);

	   scoreLayer = ScoreLayer::create();
	   this->addChild(scoreLayer,1);

	   gameLayer = GameLayer::create();
	   gameLayer->setPhyWorld(this->getPhysicsWorld());//add this layer to the scene's physical world
	   gameLayer->setscoreDelegator(scoreLayer);
	   this->addChild(gameLayer);

	   touchLayer = TouchLayer::create();
	   touchLayer->setTouchDelegator(gameLayer);
	   this->addChild(touchLayer);



      return true;  
   }while(0);
      return false;
}
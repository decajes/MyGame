#include "StartLayer.h"
#include "WelcomeLayer.h"
#include "UserData.h"
//#include "GameAudio.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

StartLayer::StartLayer(void)
{
}


StartLayer::~StartLayer(void)
{
}

Scene* StartLayer::createScene()
{
	Scene* scene = Scene::create();
	StartLayer* layer = new StartLayer();
	layer->init();
	scene->addChild(layer);
	return scene;
}

bool StartLayer::init()
{
  do
  {
	  CC_BREAK_IF(!Layer::init());

	  auto loadingSprite = Sprite::create("Loading.png");
	  loadingSprite->setAnchorPoint(Point::ZERO);
	  loadingSprite->setPosition(Point::ZERO);
	  this->addChild(loadingSprite);

	  Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(StartLayer::loadingCallBack, this));
	  
	return true;
  }while(0);
    
  return false;
}

void StartLayer::preLoadResoure()
{
	//prelaod the bird animation
	auto birdAnimation = Animation::create();
	birdAnimation->setDelayPerUnit(0.1f);
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_0.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_1.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bird_0_2.png"));
	AnimationCache::getInstance()->addAnimation(birdAnimation,"birdAnimation");

	UserData::getInstance()->saveUserData("bestScore",0);

	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.mp3");
	//GameAudio::getInstance();
}


void StartLayer::loadingCallBack(Texture2D* texture)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);
	preLoadResoure();

	auto scene = WelcomeLayer::createScene();
	TransitionScene* transition = TransitionFade::create(2.0f, scene);
	Director::getInstance()->replaceScene(transition);
}
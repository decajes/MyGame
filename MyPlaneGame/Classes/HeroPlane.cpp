#include "HeroPlane.h"
#include "GameScene.h"

USING_NS_CC;
static HeroPlane* _heroPlane = NULL;

HeroPlane::HeroPlane(void)
{
}


HeroPlane::~HeroPlane(void)
{
}

HeroPlane* HeroPlane::getInstance()
{
   if(NULL == _heroPlane)
   {
      _heroPlane = new HeroPlane();
	  _heroPlane->init();
   }
   
   return _heroPlane;
}

bool HeroPlane::init()
{
   do
   {
	   //添加飞机精灵
	   auto winSize = Director::getInstance()->getWinSize();
	   _hero = Sprite::createWithSpriteFrameName("hero1.png");
	   _hero->setPosition(Point(winSize.width*0.5, _hero->getContentSize().height));
	   this->addChild(_hero,6);

	   //创建初始化闪烁动画
	   auto blink = Blink::create(1.0f, 3);
	   //创建飞机飞行动画
	   auto planeAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("heroAnimation"));
	   
	   _hero->runAction(blink);
	   _hero->runAction(RepeatForever::create(planeAnimate));

	   return true;
   }while(0);

       return false;
}

//飞机爆炸处理
void HeroPlane::blowUp()
{
	auto blowup = Animate::create(AnimationCache::getInstance()->getAnimation("heroBlowupAnimation"));
	auto hide = Hide::create();
	auto callback = CallFunc::create(CC_CALLBACK_0(HeroPlane::callBack, this));
    _hero->stopAllActions();
	_hero->runAction(Sequence::create(blowup, hide, callback, NULL));
}

//敌机爆炸之后的返回处理，这里主要是进行gameover的处理
void HeroPlane::callBack()
{
	_hero->stopAllActions();
	_hero->removeFromParentAndCleanup(true);
	this->destroyInstance();
	GameScene* gameScene = (GameScene*)(this->getParent()->getParent());
	gameScene->gameOver();
}

//处理销毁单例
void HeroPlane::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_heroPlane);
}

#include "bird.h"
USING_NS_CC;

static bird* mybird = NULL;
const int BIRD_RADIUS = 15;

bird::bird(void)
{
}


bird::~bird(void)
{

}

bird* bird::getInstance()
{
   if(mybird == NULL)
   {
	   mybird = new bird();
	   mybird->init();
   }

   return mybird;
}


bool bird::init()
{
  do
  {
	  //get the window's size
	  Size winSize = Director::getInstance()->getWinSize();
	  
	  //initialize the bird sprite
	  birdSprite = Sprite::create();
	  this->addChild(birdSprite);

	  //get the bird animation and run it
	  auto birdAnimate = Animate::create(AnimationCache::getInstance()->animationByName("birdAnimation"));
	  birdSprite->runAction(RepeatForever::create(birdAnimate));



     
	  return true;
  }while(0);

     return false;
}

void bird::setBirdPhysics()
{
   	  auto birdBody = PhysicsBody::createCircle(BIRD_RADIUS);
	  //Point test = birdBody->getPositionOffset();
	  birdBody->setDynamic(true);
	  birdBody->setContactTestBitmask(1);
	  birdBody->setGravityEnable(false);
	  birdSprite->setPhysicsBody(birdBody);
}

void bird::releaseBrid()
{
	//this->removeChild(mybird, true);
	CC_SAFE_RELEASE_NULL(mybird);
}
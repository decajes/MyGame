#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

Hero::Hero(void)
{
}


Hero::~Hero(void)
{
}

bool Hero::init()
{
   do
   {
	   this->initWithSpriteFrameName("hero_idle_00.png");

	   Animation *pIdle = this->createAnimation("hero_idle_0%d.png", 6, 12);
	   this->setIdleAction(RepeatForever::create(Animate::create(pIdle)));

	   Animation *pWalk = this->createAnimation("hero_walk_0%d.png", 7, 14);
	   this->setWalkAction(RepeatForever::create(Animate::create(pWalk)));

	   Animation *pAttack = this->createAnimation("hero_attack_00_0%d.png", 3, 20);
	   this->setAttackAction(Sequence::create(Animate::create(pAttack), BaseSprite::createIdleCallbackFunc(), NULL));

	   Animation *pHurt = this->createAnimation("hero_hurt_0%d.png", 3, 12);
	   this->setHurtAction(Sequence::create(Animate::create(pHurt), BaseSprite::createIdleCallbackFunc(), NULL));

	   Animation *pDead = this->createAnimation("hero_knockout_0%d.png", 5, 12);
	   this->setDeadAction(Sequence::create(Animate::create(pDead), Blink::create(3, 9), BaseSprite::createDeadCallbackFunc(), NULL));

	   Size heroShowSize = this->getDisplayFrame()->getRect().size;
	   this->m_bodyBox = this->createBoundingBox(Point(-heroShowSize.width/2, -heroShowSize.height/2), heroShowSize);
	   this->m_hitBox = this->createBoundingBox(Point(heroShowSize.width/2, -10), Size(20, 20));

	 return true;
   }while(0);
     return false;
}

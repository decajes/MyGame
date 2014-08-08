#include "Pipe.h"
USING_NS_CC;

enum
{
	PIPE_DOWN = 0,
	PIPE_UP
};

const int Pipe_Distance = 100;


Pipe::Pipe(void)
{
}


Pipe::~Pipe(void)
{
}

bool Pipe::init()
{
  do
  {
	  Size winSize = Director::getInstance()->getWinSize();
	  
	  pipeDown = Sprite::createWithSpriteFrameName("pipe_down.png");
	  pipeUp = Sprite::createWithSpriteFrameName("pipe_up.png");
	  pipeDown->setPosition(0, winSize.height);
	  pipeUp->setPosition(0, pipeDown->getPosition().y-pipeDown->getContentSize().height-Pipe_Distance);
	  this->addChild(pipeDown, 0, PIPE_DOWN);
	  this->addChild(pipeUp, 0, PIPE_UP);

	  auto pipeBody = PhysicsBody::create();
	  pipeBody->addShape(PhysicsShapeBox::create(pipeDown->getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT, pipeDown->getPosition()));
	  pipeBody->addShape(PhysicsShapeBox::create(pipeUp->getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT,pipeUp->getPosition()));
	  pipeBody->setDynamic(false);
	  pipeBody->setContactTestBitmask(1);
	  this->setPhysicsBody(pipeBody);
	 /* pipeDown->setPhysicsBody(pipeDownBody);
	  pipeUp->setPhysicsBody(pipeUpBody);*/

	  
	return true;
  }while(0);

    return false;
}
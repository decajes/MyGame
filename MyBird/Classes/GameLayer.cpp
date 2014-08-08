#include "GameLayer.h"
//#include "GameAudio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

const int pipeCount = 2;
const int Pipe_Interval = 200;
const int Pipe_Height = 320;
const int Pipe_Width = 52;
const int Land_Height = 112;

enum
{
	PIP_NEW = 0,
	PIP_PASS
};

/*offset：重心点
velocity：速度 
dadamping：阻尼 
rerestitution：弹力 
mamaterial：材质 
mass：质量
moment：力矩，当他碰到另一个刚体时候 ，会产生一股扭转力，做旋转运动
body：刚体，表示物理世界中的抽象实体，附带有物理属性
shape：刚体的形状，同一个body可以附加多个shape 该shape们不会发生碰撞
joint：关节，可以连接>=2个刚体 */

GameLayer::GameLayer(void)
{

}


GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
   	  do
	  {
		  score = 0;
	      gameStatus = GAME_READY;
		  Size winSize = Director::getInstance()->getWinSize();
		  
		  //create a bird sprite
		  mybird = bird::getInstance();
		  mybird->setPosition(winSize.width*0.25, winSize.height*0.5);
		  bird::getInstance()->setBirdPhysics();
		  this->addChild(mybird, 2);

		  //add the ready mark
		  getReady = Sprite::createWithSpriteFrameName("getReady.png");
		  getReady->setPosition(winSize.width*0.5, winSize.height*0.75);
		  this->addChild(getReady);
		  
		  tapToStart = Sprite::createWithSpriteFrameName("tapToStart.png");
		  tapToStart->setPosition(winSize.width*0.5, winSize.height*0.5);
		  this->addChild(tapToStart);

		  //add the landnode 
		  auto groundNode = Node::create();
		  auto groundBody = PhysicsBody::createEdgeBox(Size(winSize.width, Land_Height));
		  groundBody->setDynamic(false);
		  groundBody->setContactTestBitmask(1);
		  groundNode->setPhysicsBody(groundBody);
		  groundNode->setPosition(winSize.width*0.5, Land_Height*0.5);
		  this->addChild(groundNode);

	      //create the land sprite, because the land need to scroll, so here create two land sprite to replace
	      land1 = Sprite::createWithSpriteFrameName("land.png");
	      land1->setAnchorPoint(Point::ZERO);
	      land1->setPosition(Point::ZERO);
		  land1->getTexture()->setAliasTexParameters();
	      this->addChild(land1, 2);

	      land2 = Sprite::createWithSpriteFrameName("land.png");
	      land2->setAnchorPoint(Point::ZERO);
	      land2->setPosition(Point(land1->getContentSize().width-2.0f, 0));
		  land2->getTexture()->setAliasTexParameters();
	      this->addChild(land2, 2);

		  this->scheduleUpdate();
	      this->schedule(schedule_selector(GameLayer::landMove),0.01f);

		  auto contactListener = EventListenerPhysicsContact::create();
		  contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
		  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	      return true;
	  }while(0);
	  return false;
}

void GameLayer::landMove(float dt)
{
    //move the land
	land1->setPositionX(land1->getPosition().x-1.0f);
	land2->setPositionX(land1->getPosition().x + land1->getContentSize().width-2.0f);
	if(land2->getPositionX() == 0)
	{
		land1->setPosition(Point::ZERO);
	}

	//move the pipe
	for(auto pip : pipeVector)
	{
		float test = pip->getPosition().x-1.0f;
		pip->setPositionX(test);
		if(pip->getPositionX() < (-Pipe_Width))
	   {
		Size winSize = Director::getInstance()->getWinSize();
		pip->setPositionX(winSize.width + Pipe_Width);
		pip->setPositionY(getRandomY());
		pip->setTag(PIP_NEW);
	   }
	}
}

float GameLayer::getRandomY()
{
	return (float)(rand()%(Pipe_Height-Land_Height)-Land_Height*0.5);
}

bool GameLayer::onContactBegin(PhysicsContact& contact)
{
	gameOver();
	return true;
}

void GameLayer::onTouch()
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.mp3");
	if(gameStatus == GAME_START)
	{
	  Vect curVelocity = bird::getInstance()->getBirdSprite()->getPhysicsBody()->getVelocity();
      bird::getInstance()->getBirdSprite()->getPhysicsBody()->setVelocity(Vect(0,MIN(200,500+curVelocity.y)));
	}
	else if(gameStatus == GAME_READY)
	{
		getReady->runAction(FadeOut::create(0.5f));
		tapToStart->runAction(FadeOut::create(0.5f));
		getReady->removeFromParent();
		tapToStart->removeFromParent();
		createPipe();
		bird::getInstance()->getBirdSprite()->getPhysicsBody()->setVelocity(Vect(0,200));
		bird::getInstance()->getBirdSprite()->getPhysicsBody()->setGravityEnable(true);
		gameStatus = GAME_START;
	}

	else;
}

void GameLayer::update(float dt)
{
	rotateBird();
	updateScore();
}

void GameLayer::rotateBird()
{
	Vect curVelocity = bird::getInstance()->getBirdSprite()->getPhysicsBody()->getVelocity();
	float angle = MIN(90,curVelocity.y*(-0.15));
	bird::getInstance()->getBirdSprite()->setRotation(angle);
}

void GameLayer::updateScore()
{
	for(auto pip : pipeVector)
	{
		if(pip->getTag()==PIP_NEW)
		{
			if(pip->getPositionX() < bird::getInstance()->getPositionX())
			{
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.mp3");
			   score++;
			   pip->setTag(PIP_PASS);
			   _scoreDelegator->showCurrentScore(score);
			}
		}
	}
}

void GameLayer::gameOver()
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.mp3");
	bird::getInstance()->getBirdSprite()->stopAllActions();
	this->unschedule(schedule_selector(GameLayer::landMove));
	this->unscheduleUpdate();
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.mp3");
	bird::getInstance()->getBirdSprite()->setRotation(90);
	//bird::getInstance()->getBirdSprite()->getPhysicsBody()->setRotationEnable(false);
	bird::getInstance()->releaseBrid();
	_eventDispatcher->removeAllEventListeners();
	_scoreDelegator->showGameOver(score);
}

void GameLayer::createPipe()
{
	Size winSize = Director::getInstance()->getWinSize();  
    for(int i = 0; i < pipeCount; i++)
    {
		Pipe* pipe = Pipe::create();
	    pipe->setTag(PIP_NEW);
		pipe->setPosition(Point(winSize.width + (i+1)*Pipe_Interval, getRandomY()));
		//pipe->setPosition(Point(winSize.width*0.5+i*50, getRandomY()));
		this->addChild(pipe);
		pipeVector.pushBack(pipe);
    }
}
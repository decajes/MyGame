#include "ScoreLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "UserData.h"
//#include "GameAudio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

const int NUMBER_INTERVAL = 20;
const int SCORE_INTERVAL = 10;

enum
{
  SCORE_COUNTER = 0,
  SCORE_BEST
};

ScoreLayer::ScoreLayer(void)
{
	finalScore = 0;
	bestScore = 0;
	counter = 0;
	getNewRecord = false;
	numberVector = Vector<SpriteFrame*>(10);
	counterVector = Vector<SpriteFrame*>(10);
}


ScoreLayer::~ScoreLayer(void)
{
}

bool ScoreLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	  for(int i = 0; i < 10; i++)
	  {
		   const char* counterString = String::createWithFormat("number_0_%d.png",i)->getCString();
		   auto counterFrame = SpriteFrameCache::getInstance()->spriteFrameByName(counterString);
		   counterVector.pushBack(counterFrame);
	   }

	  for(int i = 0; i < 10; i++)
	  {
		   const char* numberString = String::createWithFormat("number%d.png",i)->getCString();
		   auto numberFrame = SpriteFrameCache::getInstance()->spriteFrameByName(numberString);
		   numberVector.pushBack(numberFrame);
	  }
	   
	  Size winSize = Director::getInstance()->getWinSize();
	  scoreNode = Node::create();
	  scoreNode->setPosition(Point(winSize.width*0.5, winSize.height*0.9));
	  numberSprite = Sprite::createWithSpriteFrame(numberVector.at(0));
	  scoreNode->addChild(numberSprite);
	  this->addChild(scoreNode);

      return true;
   }while(0);
      return false;
}

void ScoreLayer::showCurrentScore(int score)
{
	numberPlace = 0;
	scoreNode->removeAllChildren();
	Size winSize = Director::getInstance()->getWinSize();
	while(score)
	{
		iterator = score%10;
		numberSprite = Sprite::createWithSpriteFrame(numberVector.at(iterator));
		numberSprite->setPosition(Point(-NUMBER_INTERVAL*numberPlace,0));
		scoreNode->addChild(numberSprite);
		numberPlace++;
		score /= 10;
	}
	 scoreNode->setPosition(winSize.width*0.5+NUMBER_INTERVAL*numberPlace/2, winSize.height*0.9);
}

void ScoreLayer::restartCallBack(Object* psender)
{
	/*this->removeChild(gameOverSprite, false);
	this->removeChild(menu, false);
	Size winSize = Director::getInstance()->getWinSize();
    counterPanel->setPosition(winSize.width*0.5, -counterPanel->getContentSize().height);*/
	Scene* gameScene = GameScene::create();
	TransitionScene* transition = TransitionFade::create(1.0f, gameScene);
	Director::getInstance()->replaceScene(gameScene);
}

void ScoreLayer::showMenu()
{
	Size winSize = Director::getInstance()->getWinSize(); 
	auto startButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("start.png"),Sprite::createWithSpriteFrameName("start.png"),NULL,CC_CALLBACK_1(ScoreLayer::restartCallBack, this));
	auto rateButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("rate.png"),Sprite::createWithSpriteFrameName("rate.png"));
	menu = Menu::create(startButton, rateButton, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	   //menu->alignItemsVerticallyWithPadding(50);
	menu->setPosition(Point(winSize.width*0.5, winSize.height*0.4));
	//auto delay = DelayTime::create(1.0f);
	auto fadeIn = FadeIn::create(1.0f);
	this->addChild(menu);
	menu->runAction(fadeIn);
}

void ScoreLayer::showScore()
{
	this->schedule(schedule_selector(ScoreLayer::countScore),0.02f);
}

void ScoreLayer::showCounterPanel()
{
	Size winSize = Director::getInstance()->getWinSize();
	counterPanel = Sprite::createWithSpriteFrameName("ScorePanel.png");
	counterPanel->setPosition(Point(winSize.width*0.5, -counterPanel->getContentSize().height));
	this->addChild(counterPanel);

	//Size panelSize = counterPanel->getContentSize();
	//scoreSprite = Sprite::createWithSpriteFrame(counterVector.at(0));
	//scoreSprite->setPosition(Point(panelSize.width-30 ,panelSize.height*0.6));
	//counterPanel->addChild(scoreSprite, 0, SCORE_COUNTER);

	//bestSprite = Sprite::createWithSpriteFrame(counterVector.at(0));			
 //   bestSprite->setPosition(Point(panelSize.width-30 ,panelSize.height*0.5));
	//counterPanel->addChild(bestSprite, 0, SCORE_BEST);

	auto flyTo = MoveTo::create(1.0f, Point(winSize.width*0.5, winSize.height*0.6));
	CallFunc* action = CallFunc::create(std::bind(&ScoreLayer::showMenu, this));
	CallFunc* ShowScore = CallFunc::create(std::bind(&ScoreLayer::showScore, this));
	CallFunc* ShowBestScore = CallFunc::create(std::bind(&ScoreLayer::showBestScore, this));
	CallFunc* ShowOther = CallFunc::create(std::bind(&ScoreLayer::showOther, this));
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.mp3");
	counterPanel->runAction(Sequence::create(flyTo, ShowScore,ShowBestScore,ShowOther, action, NULL));
}

void ScoreLayer::showOther()
{
	showMedal();
	showNewSprite();
}

void ScoreLayer::showGameOverSprite()
{
    Size winSize = Director::getInstance()->getWinSize();
	gameOverSprite = Sprite::createWithSpriteFrameName("gameOver.png");
	gameOverSprite->setPosition(Point(winSize.width*0.5, winSize.height*0.8));
	this->addChild(gameOverSprite);
	auto fadeIn = FadeIn::create(1.0f);
	CallFunc* action = CallFunc::create(std::bind(&ScoreLayer::showCounterPanel, this));
	gameOverSprite->runAction(Sequence::create(fadeIn,action,NULL));
	
}

void ScoreLayer::showGameOver(int score)
{
	this->finalScore = score;
	scoreNode->removeAllChildren();
	showGameOverSprite();
	//showCounterPanel(score);
	//showMenu();
}

void ScoreLayer::countScore(float dt)
{
	if(counter <= finalScore)
	{
	int score = counter;
	if(counterPanel->getChildByTag(SCORE_COUNTER))
	{
	  counterPanel->removeChildByTag(SCORE_COUNTER, true);
	}
	numberPlace = 0;
	Size panelSize = counterPanel->getContentSize();
	do
	 {
		iterator = score%10;
		scoreSprite = Sprite::createWithSpriteFrame(counterVector.at(iterator));
		scoreSprite->setPosition(Point((panelSize.width-30-SCORE_INTERVAL*numberPlace) ,panelSize.height*0.6));
		counterPanel->addChild(scoreSprite, 0, SCORE_COUNTER);
		numberPlace++;
		score /= 10;
	 }while(score);
	 counter++;
	}
	else
	{
		this->unschedule(schedule_selector(ScoreLayer::countScore));
	}
}

void ScoreLayer::showBestScore()
{
	bestScore = UserData::getInstance()->readUserData("bestScore");
	Size panelSize = counterPanel->getContentSize();

	if(bestScore < finalScore)
	{
	   bestScore = finalScore;
	   getNewRecord = true;
	   UserData::getInstance()->saveUserData("bestScore", bestScore);
	}
	
	numberPlace = 0;
    do
	 {
		iterator = bestScore%10;
		bestSprite = Sprite::createWithSpriteFrame(counterVector.at(iterator));
		bestSprite->setPosition(Point((panelSize.width-30-SCORE_INTERVAL*numberPlace) ,panelSize.height*0.25));
		counterPanel->addChild(bestSprite, 0, SCORE_BEST);
		numberPlace++;
		bestScore /= 10;
	 }while(bestScore);
}

void ScoreLayer::showMedal()
{
	if(finalScore < 10)
	{
		medalSprite = Sprite::createWithSpriteFrameName("bronze_medal.png");
	}
	else if(finalScore < 50)
	{
	    medalSprite = Sprite::createWithSpriteFrameName("silver_medal.png");
	}
	else
	{
	    medalSprite = Sprite::createWithSpriteFrameName("gold_medal.png");
	}
	medalSprite->setPosition(Point(48, counterPanel->getContentSize().height*0.48));
	counterPanel->addChild(medalSprite);

	auto scale = ScaleBy::create(0.5f, 2.0f);
	auto reverse = scale->reverse();
	auto blink = Blink::create(0.5f, 2);
	medalSprite->runAction(Sequence::create(scale, reverse, blink, NULL));
}

void ScoreLayer::showNewSprite()
{ 
	if(getNewRecord)
	{
	   Size panelSize = counterPanel->getContentSize();
	   auto newSprite = Sprite::createWithSpriteFrameName("newRecord.png");
	   newSprite->setPosition(Point((panelSize.width-60) ,panelSize.height*0.25));
	   counterPanel->addChild(newSprite);
	   newSprite->setRotation(-30);
	   auto scale = ScaleBy::create(1.0f, 2.0f);
	   auto reverse = scale->reverse();
	   auto seq = Sequence::create(scale, reverse, NULL);
	   newSprite->runAction(Repeat::create(seq, 3));
	}
}
#include "GameOverLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

GameOverLayer::GameOverLayer(void)
{
	//初始化变量
	finalScore = 0;
	getRecord = false;
}


GameOverLayer::~GameOverLayer(void)
{
}

Scene* GameOverLayer::scene(int score)
{
   Scene* gameOverScene = Scene::create();
   GameOverLayer* gameOverLayer = GameOverLayer::create(score);
   gameOverScene->addChild(gameOverLayer);
   return gameOverScene;
}

GameOverLayer* GameOverLayer::create(int score)
{
	GameOverLayer* pRet = new GameOverLayer();
	pRet->finalScore = score;
	if(pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
	    delete pRet;
		pRet = NULL;
		return pRet;
	}
}

bool GameOverLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("game_over.mp3");

	   //添加游戏结束背景
	   Sprite* gameOverGround = Sprite::createWithSpriteFrameName("gameover.png");
	   gameOverGround->setAnchorPoint(Point::ZERO);
	   gameOverGround->setPosition(Point::ZERO);
	   this->addChild(gameOverGround);

	   //创建一个动作来顺序执行分数统计，最高分数展示，新纪录表现显示，菜单显示
	   auto countscore = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showCurrentScore, this));
	   auto showbestscore = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showBestScore, this));
	   auto delay = DelayTime::create(1.0f);
	   auto showbestsprite = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showBestSprite, this));
	   auto showmenu = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showMenu, this));
	   auto seq = Sequence::create(countscore, showbestscore, delay, showbestsprite, showmenu, NULL);
	   gameOverGround->runAction(seq);


	   return true;
   }while(0);
       
       return false;
}

void GameOverLayer::reset()
{
	Scene* gameScene = TransitionSlideInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameScene);
}

void GameOverLayer::showCurrentScore()
{
    auto winSize = Director::getInstance()->getWinSize();
	scoreLabel = Label::createWithBMFont("font.fnt", "0");
	scoreLabel->setPosition(winSize.width*0.5, winSize.height*0.55);
	this->addChild(scoreLabel);
	for(int i = 1; i <= finalScore; i++)
	{
	     String* strScore = String::createWithFormat("%d", i); 
		 scoreLabel->setString(strScore->getCString());
	}
	
}

//如果当前分数超过历史最高分的时候重新保存当前分数为最高分数
void GameOverLayer::showBestScore()
{
	int bestScore = UserData::getInstance()->readUserData("best_score");
	if(finalScore > bestScore)
	{
		UserData::getInstance()->saveUserData("best_score", finalScore);
		bestScore = finalScore;
		getRecord = true;
	}
	auto winSize = Director::getInstance()->getWinSize();
	auto strBestScore = String::createWithFormat("%d", bestScore);
	auto bestScoreLabel = Label::createWithBMFont("font.fnt", strBestScore->getCString());
	bestScoreLabel->setPosition(winSize.width*0.5, winSize.height*0.7);
	this->addChild(bestScoreLabel);
}

void GameOverLayer::showBestSprite()
{
	if(getRecord)
	{
	  auto winSize = Director::getInstance()->getWinSize();
	  auto bewRecord = Sprite::createWithSpriteFrameName("NewRecord.png");
	  auto scaleTo = ScaleBy::create(0.5f, 2.0f);
	  auto reverse = scaleTo->reverse();
	  auto seq = Sequence::create(scaleTo, reverse, NULL);
	  bewRecord->setPosition(winSize.width*0.5, winSize.height*0.4);
	  this->addChild(bewRecord);
	  bewRecord->runAction(Repeat::create(seq, 2));
	  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("achievement.mp3");
	}
}

void GameOverLayer::showMenu()
{
  	auto winSize = Director::getInstance()->getWinSize();
	auto backGameButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("btn_finish.png"), Sprite::createWithSpriteFrameName("btn_finish.png"), NULL, CC_CALLBACK_0(GameOverLayer::reset, this));
	auto menu = Menu::create(backGameButton, NULL);
	menu->setPosition(winSize.width*0.5, winSize.height*0.25);
	this->addChild(menu);
}
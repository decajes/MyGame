#include "ControlLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static const Size size = Size(60, 45);

ControlLayer::ControlLayer(void)
{
	level = 1;
	levelfactor = 1;
	levelscore = 50;
}


ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());
	   auto winSize = Director::getInstance()->getWinSize();

	   //添加暂停菜单按钮
	   pauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_pause_nor.png"),Sprite::createWithSpriteFrameName("game_pause_pressed.png"),CC_CALLBACK_0(ControlLayer::pauseCallBack, this));   
	   auto menu = Menu::create(pauseItem, NULL);
	   menu->setPosition(size.width*0.6, winSize.height-size.height*0.6);
	   this->addChild(menu);

	   //添加分数演示标签
	   scoreLabel = Label::createWithBMFont("font.fnt", "0");
	   scoreLabel->setPosition(winSize.width-50, winSize.height-20);
	   this->addChild(scoreLabel);

	   return true;
   }while(0);

   return false;
}

//暂停返回事件
void ControlLayer::pauseCallBack()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	//若是未暂停状态则执行暂停处理
	if(!Director::getInstance()->isPaused())
	{
		//此处添加暂停处理代码

		//把暂停标签按钮设置为恢复游戏的样式
		pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png")); 
		pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		//执行暂停
		GameScene* gameScene = (GameScene*)this->getParent();
		gameScene->pause();
	}
	else//若已经暂停，再次点击按钮则执行恢复游戏处理
	{
	    //把恢复标签设置为暂停游戏的样式
		pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png")); 
		pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		//执行恢复
		GameScene* gameScene = (GameScene*)this->getParent();
		gameScene->resume();
	}
}

//更新分数，主要用label的setString来实现
void ControlLayer::updateScore(int score)
{
	String* scoreString = String::createWithFormat("%d", score);
	scoreLabel->setString(scoreString->getCString());
	if(level < 4)
	{
		setLevel(score);
	}
}

void ControlLayer::setLevel(int score)
{
	if(score > levelscore)
	{
	  level++;
	  levelfactor -= 0.3;
	  levelscore += 50;
	  GameScene* gameScene = (GameScene*)this->getParent();
	  gameScene->changeLevel(levelfactor);
	}
}


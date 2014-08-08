#include "UfoLayer.h"
#include "GameScene.h"
//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;
USING_NS_CC;
enum
{
  BOMB_ITEM = 0,
  BOMB_NUM
};

UfoLayer::UfoLayer(void)
{
}

UfoLayer::~UfoLayer(void)
{
}

bool UfoLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   this->m_bombNum = 0;
	   this->schedule(schedule_selector(UfoLayer::addUfo), 10.0f, kRepeatForever, 5.0f);

	   return true;
   }while(0);
       return false;
}

//添加ufo
void UfoLayer::addUfo(float dt)
{
	int isaddufo = (int)(CCRANDOM_0_1()*2);
	do
	{
	  CC_BREAK_IF(isaddufo);
	  //随机生成ufo
	  int type = (int)(CCRANDOM_0_1()*2+1);
	  String* ufoName = String::createWithFormat("ufo%d.png", type);
	  auto ufoSprite = Sprite::createWithSpriteFrameName(ufoName->getCString());
	  this->addChild(ufoSprite, 5, type);
	  this->ufoMove(ufoSprite, getRandomPosition(ufoSprite->getContentSize()));
	  //添加到ufo管理容器中去
	  _ufoVector.pushBack(ufoSprite);
	}while(0);
}

//移动ufo
void UfoLayer::ufoMove(Sprite* ufo,Point origin)
{
	ufo->setPosition(origin);
	auto winSize = Director::getInstance()->getWinSize();
	auto destination = Point(origin.x, winSize.height-origin.y);
	int speed = 200;
	float duration = (origin.y-destination.y)/speed;

	auto moveTo = MoveTo::create(duration, destination);
	auto callback = CallFunc::create(CC_CALLBACK_0(UfoLayer::moveEnd, this, ufo));
	ufo->runAction(Sequence::create(moveTo, callback, NULL));
}

//随机获得初始位置
Point UfoLayer::getRandomPosition(Size size)
{
	auto winSize = Director::getInstance()->getWinSize();
	int posY = winSize.height + size.height*0.5;
	int posX = rand()%(int)(winSize.width - size.width) + size.width*0.5;
	return Point(posX, posY);
}

//移动完之后删除并移除出ufo容器
void UfoLayer::moveEnd(Sprite* ufo)
{
	ufo->removeFromParentAndCleanup(false);
	_ufoVector.eraseObject(ufo);
}

//ufo碰撞处理
void UfoLayer::collision(Sprite* ufo)
{
	ufo->stopAllActions();
	_ufoVector.eraseObject(ufo);
	ufo->removeFromParentAndCleanup(false);
}

//添加bomb的按钮
void UfoLayer::addBombItem()
{
	auto bombItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bomb.png"),Sprite::createWithSpriteFrameName("bomb.png"),CC_CALLBACK_0(UfoLayer::subBombNum, this));
	auto bombItemSize = bombItem->getContentSize();
	auto menu = Menu::create(bombItem, NULL);
	menu->setPosition(bombItemSize.width*0.5, bombItemSize.height*2);
	this->addChild(menu, 0, BOMB_ITEM);

	bombCount = Label::createWithBMFont("font.fnt", "1");
	bombCount->setPosition(63*1.5, 57*2);
	this->addChild(bombCount, 0, BOMB_NUM);
}

//碰撞到飞机之后更新bomb的数目
void UfoLayer::updateBombNum()
{

	if(m_bombNum > 0)
	{
		String* num = String::createWithFormat("X%d", m_bombNum);
		bombCount->setString(num->getCString());
	}
}

void UfoLayer::addBombNum()
{
	m_bombNum++;

	if(!this->getChildByTag(BOMB_ITEM))
	{
		this->addBombItem();
	}

	this->updateBombNum();
}
	
void UfoLayer::subBombNum()
{
	m_bombNum--;

	if(m_bombNum <= 0)
	{
		this->removeChildByTag(BOMB_ITEM, true);
		this->removeChildByTag(BOMB_NUM, true);
	}
	//SimpleAudioEngine::getInstance()->playEffect("use_bomb.mp3");
	this->destroyAllEnemy();
	this->updateBombNum();
}

//点击bomb按钮之销毁当前所有敌机
void UfoLayer::destroyAllEnemy()
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->eliminateAllEnemy();
}





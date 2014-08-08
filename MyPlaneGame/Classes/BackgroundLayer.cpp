#include "BackgroundLayer.h"
USING_NS_CC;

BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   background1 = Sprite::createWithSpriteFrameName("background.png");
	   background1->setAnchorPoint(Point::ZERO);
	   background1->setPosition(Point::ZERO);
	   //原来出现的白边现在解决了，就是调用下面一句代码将精灵照片设置为无锯齿
	   background1->getTexture()->setAliasTexParameters();
	   this->addChild(background1);

	   background2 = Sprite::createWithSpriteFrameName("background.png");
	   background2->setAnchorPoint(Point::ZERO);
	   background2->setPosition(Point(0, background2->getContentSize().height - 2.0f));
	   background2->getTexture()->setAliasTexParameters();
	   this->addChild(background2);

	   this->schedule(schedule_selector(BackgroundLayer::backgroundMove),0.01f);

      return true;
   }while(0);
      return false;
}

//设置两个图片的滚动模拟飞机在运动
void BackgroundLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2.0f);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2.0f);
	if(0 == background2->getPositionY())
	{
		background1->setPositionY(0);
	}
}

#include "OperateLayer.h"
#include "Hero.h"

USING_NS_CC;

OperateLayer::OperateLayer(void):
	m_pJoystick(NULL),
	m_pJoystickBg(NULL)
{
}


OperateLayer::~OperateLayer(void)
{
}

bool OperateLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   m_pJoystick = Sprite::create("joystick.png");
	   m_pJoystickBg = Sprite::create("joystick_bg.png");
	   this->addChild(m_pJoystick, 1);
	   this->addChild(m_pJoystickBg, 0);

	   this->hideJoystick();

	   auto listener = EventListenerTouchAllAtOnce::create();
	   listener->onTouchesBegan = CC_CALLBACK_2(OperateLayer::onTouchesBegan, this);
	   listener->onTouchesMoved = CC_CALLBACK_2(OperateLayer::onTouchesMoved, this);
	   listener->onTouchesEnded = CC_CALLBACK_2(OperateLayer::onTouchesEnded, this);
	   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	   /*auto listener = EventListenerTouchOneByOne::create();
	   listener->onTouchBegan = CC_CALLBACK_2(OperateLayer::onTouchBegan, this);
	   listener->onTouchMoved = CC_CALLBACK_2(OperateLayer::onTouchEnded, this);
	   listener->onTouchEnded = CC_CALLBACK_2(OperateLayer::onTouchEnded, this);
	   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	   return true;
   }while(0);
       return false;
}

void OperateLayer::showJoystick(Point pos)
{
	m_pJoystick->setPosition(pos);
	m_pJoystickBg->setPosition(pos);

	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void OperateLayer::hideJoystick()
{
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	m_pJoystickBg->setVisible(false);	
}

//这几个数字的意义不是很明白！！！！
void OperateLayer::updateJoystick(Point direction, float distance)
{
	Point start = m_pJoystickBg->getPosition();

	if(distance < 33)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}else if(distance > 78){
		m_pJoystick->setPosition(start + (direction * 45));
	}else{
		m_pJoystick->setPosition(start + (direction * 33));
	}
}

void OperateLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	while(touchIter != touches.end())
	{
	    Touch *pTouch = (Touch*)(*touchIter);
		Point p = pTouch->getLocation();
		if(p.x <= winSize.width / 2)
		{
			this->showJoystick(p);
		}else{
			m_pHero->attack();
		}

		++ touchIter;
	}
}

void OperateLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	while(touchIter != touches.end())
	{
	Touch *pTouch = (Touch*)(*touchIter);
	Point start = pTouch->getStartLocation();
	if(start.x > winSize.width/2)
	{
		++ touchIter;
		return;
	}
	Point dest = pTouch->getLocation();
	float distance = start.getDistance(dest);
	Point direction = (dest - start).normalize();//计算两点单位向量
	this->updateJoystick(direction, distance);
	m_pHero->walk(direction, distance);
	++ touchIter;
	}
}

void OperateLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
	this->hideJoystick();
	m_pHero->stop();
}


//bool OperateLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
//{
//	Size winSize = Director::getInstance()->getWinSize();
//	Point p = touch->getLocation();
//	if(p.x <= winSize.width / 2)
//	{
//		this->showJoystick(p);
//	}else{
//			//m_pHero->attack();
//	}
//	return true;
//}
//
//void OperateLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
//{
//	Size winSize = Director::getInstance()->getWinSize();
//
//	Point start = touch->getStartLocation();
//	if(start.x > winSize.width/2)
//	{
//		return;
//	}
//	Point dest = touch->getLocation();
//	float distance = start.getDistance(dest);
//	Point direction = (dest - start).normalize();//计算两点单位向量
//	this->updateJoystick(direction, distance);
//	//m_pHero->walk(direction, distance);
//}
//
//void OperateLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
//{
//	this->hideJoystick();
//}
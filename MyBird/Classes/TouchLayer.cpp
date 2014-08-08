#include "TouchLayer.h"

USING_NS_CC;

TouchLayer::TouchLayer(void)
{
}


TouchLayer::~TouchLayer(void)
{
}

bool TouchLayer::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());

		auto touchListener = EventListenerTouchAllAtOnce::create();
		touchListener->onTouchesBegan = CC_CALLBACK_2(TouchLayer::onTouchesBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	  return true;
	}while(0);
	  return false;
}

void TouchLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
	_touchDelegator->onTouch();
}

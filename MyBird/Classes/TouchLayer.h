#pragma once
#include "cocos2d.h"

class TouchDelegate
{
public:
	virtual void onTouch()=0;
};

class TouchLayer : public cocos2d::Layer
{
public:
	TouchLayer(void);
	~TouchLayer(void);
	CREATE_FUNC(TouchLayer);
	bool init();

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	CC_SYNTHESIZE(TouchDelegate*, _touchDelegator, TouchDelegator);

};


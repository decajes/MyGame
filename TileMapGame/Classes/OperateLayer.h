#pragma once
#include "cocos2d.h"

class Hero;

class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer(void);
	~OperateLayer(void);
	virtual bool init();
	CREATE_FUNC(OperateLayer);

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	//bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	//void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	//void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	CC_SYNTHESIZE(Hero*, m_pHero, Hero);

private:
	void showJoystick(cocos2d::Point pos);
	void hideJoystick();
	void updateJoystick(cocos2d::Point directon, float distance);

	cocos2d::Sprite *m_pJoystick;
	cocos2d::Sprite *m_pJoystickBg;
};


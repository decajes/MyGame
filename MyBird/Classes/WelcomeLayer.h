#pragma once
#include "cocos2d.h"

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);
	static cocos2d::Scene* createScene();
	bool init();

private:
	void landMove(float dt);
	cocos2d::Sprite* land1;
	cocos2d::Sprite* land2;
	void startCallBack(cocos2d::Object* psender);
};


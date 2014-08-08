#pragma once
#include "cocos2d.h"

class bird : public cocos2d::Node
{
public:
	bird(void);
	~bird(void);
	static bird* getInstance();
	bool init();
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, birdSprite, BirdSprite);
    void setBirdPhysics();
	void releaseBrid();
};


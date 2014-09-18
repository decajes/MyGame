#pragma once
#include "BaseSprite.h"

class Hero : public BaseSprite
{
public:
	Hero(void);
	~Hero(void);

	bool init();
	CREATE_FUNC(Hero);
	std::function<void(cocos2d::Point, float)> walk;
	std::function<void(void)> stop;
};


#pragma once
#include "cocos2d.h"
#include <time.h>


class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);

	CREATE_FUNC(BackgroundLayer);
	bool init();
	
private:
	cocos2d::Sprite* background;

};


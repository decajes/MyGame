#pragma once
#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);
	CREATE_FUNC(BackgroundLayer);
	bool init();

private:
	//图片滚动
	void backgroundMove(float dt);
	//定义两个背景精灵
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
};


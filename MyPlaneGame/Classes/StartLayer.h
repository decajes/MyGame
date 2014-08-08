#pragma once
#include "cocos2d.h"
class StartLayer : public cocos2d::Layer
{
public:
	StartLayer(void);
	~StartLayer(void);
	CREATE_FUNC(StartLayer);
	bool init();
	static cocos2d::Scene* scene();
	//预处理数据
	void preLoadResource();
	//场景切换
	void transition();
};


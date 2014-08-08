#pragma once
#include "cocos2d.h"

class StartLayer : public cocos2d::Layer
{
public:
	StartLayer(void);
	~StartLayer(void);
	static cocos2d::Scene* createScene();
	bool init();

private:
	void preLoadResoure();
	void loadingCallBack(cocos2d::Texture2D* texture);
};


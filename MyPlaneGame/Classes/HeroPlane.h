#pragma once
#include "cocos2d.h"


class HeroPlane : public cocos2d::Node
{
public:
	HeroPlane(void);
	~HeroPlane(void);

	//把英雄飞机设置成为单例
	static HeroPlane* getInstance();
	//销毁单例
	void destroyInstance();
	bool init();
	//飞机爆炸
	void blowUp();
	//爆炸返回操作
	void callBack();
	//定义一个只读精灵
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite* , _hero, Hero);

	//获取英雄飞机有效的触点范围
	//cocos2d::Rect getHeroPlaneTouchRect();

};


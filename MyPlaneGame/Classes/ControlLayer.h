#pragma once
#include "cocos2d.h"

class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);
	CREATE_FUNC(ControlLayer);
	bool init();
	//游戏暂停按钮返回事件
	void pauseCallBack();
	//更新分数
	void updateScore(int score);
	//设置等级
	void setLevel(int score);
private:
	cocos2d::MenuItemSprite* pauseItem;
	cocos2d::Label* scoreLabel;
	int level;
	float levelfactor;
	int levelscore;
};


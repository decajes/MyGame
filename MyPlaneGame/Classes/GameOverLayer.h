#pragma once
#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	static cocos2d::Scene* scene(int score);
	static GameOverLayer* create(int score);
	bool init();
	//重新开始游戏
	void reset();
	//显示当前分数
	void showCurrentScore();
	//显示最高得分
	void showBestScore();
	//创纪录时显示标志
	void showBestSprite();
	//显示菜单栏
	void showMenu();
private:
	int finalScore;
	bool getRecord;
	cocos2d::Label* scoreLabel;


};


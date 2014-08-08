#pragma once
#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	//创建敌机精灵
	static Enemy* createEnemy();
	void initEnemyWithFrameName(std::string filename);

	//随机获得敌机发射位置
	cocos2d::Point getEnemyOriginPosition(cocos2d::Size enemySize);
	//随机获得初始速度
	int getSpeed();
	//敌机下落
	void enemyFly(cocos2d::Point pos);
	//敌机销毁
	void FlyEnd();
	//敌机爆炸
	void enemyBlowUp(std::string animationName);
	//设置生命值
	void setLife(int life);
	//判断是否死亡
	bool isDead();
private:
	int m_life;
};


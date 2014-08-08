#pragma once
#include "cocos2d.h"
#include "Enemy.h"

class EnemyLayer : public cocos2d::Layer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	bool init();
	//定义3种敌机的管理容器
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy1Vector, Enemy1Vector);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy2Vector, Enemy2Vector);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy3Vector, Enemy3Vector);
	//添加敌机
	void addEnemy1(float dt);
	void addEnemy2(float dt);
	void addEnemy3(float dt);
	//移除指定敌机
	void removeEnemy(Enemy* enemy);
	//设置游戏难度
	void setLevelFactor(float factor);
	//开启敌机发射
	void startEnemy(float factor);
	//停止敌机发射
	void stopEnemy();
	//void removeAllEnemy();
};


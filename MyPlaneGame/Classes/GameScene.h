#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "Weapon.h"
#include "EnemyLayer.h"
#include "UfoLayer.h"
#include "ControlLayer.h"
#include "GameOverLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);

	CREATE_FUNC(GameScene);
	bool init();
	void update(float dt);
	void eliminateAllEnemy();
	void pause();
	void resume();
	//CC_SYNTHESIZE_READONLY(int,m_score,Score);
	void gameOver();
	void changeLevel(float factor);

private:
	//void preloadresource();//实现载入后删除	
	void checkHeroPlaneWithEnemyCollision();//检测敌机与飞机的碰撞
	void checkBulletWithEnemyCollision(); //检测子弹与敌机的碰撞
	void checkHeroPlaneWithUFOCollision();//检测ufo和飞机的碰撞
	
	int m_score;
    
	BackgroundLayer* backgroundLayer;
	Weapon* weapon;
	EnemyLayer* enemyLayer;
	UfoLayer* ufoLayer;
	ControlLayer* controlLayer;
};


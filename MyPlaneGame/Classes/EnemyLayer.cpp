#include "EnemyLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

EnemyLayer::EnemyLayer(void)
{
}


EnemyLayer::~EnemyLayer(void)
{
}

bool EnemyLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());
	   
	   //开启敌机的发射
	   this->startEnemy(1);


	    return true; 
   }while(0);
	   
	   return false;
}

//添加敌机1
void EnemyLayer::addEnemy1(float dt)
{
	//创建对象
	Enemy* enemy1 = Enemy::createEnemy();
	enemy1->initEnemyWithFrameName("enemy1.png");
	//设置生命值
	enemy1->setLife(1);
	this->addChild(enemy1,2);
	//添加到敌机1的容器中
	_enemy1Vector.pushBack(enemy1);
	//设置敌机飞行
	enemy1->enemyFly(enemy1->getEnemyOriginPosition(Size(57,43)));
}

//添加敌机2
void EnemyLayer::addEnemy2(float dt)
{
	Enemy* enemy2 = Enemy::createEnemy();
	enemy2->initEnemyWithFrameName("enemy2.png");
	enemy2->setLife(5);
	this->addChild(enemy2,3);
	_enemy2Vector.pushBack(enemy2);
	enemy2->enemyFly(enemy2->getEnemyOriginPosition(Size(69,99)));
}

//添加敌机3
void EnemyLayer::addEnemy3(float dt)
{	
	Enemy* enemy3 = Enemy::createEnemy();
	enemy3->setLife(15);
	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy3Animation"));
	enemy3->runAction(RepeatForever::create(animate));
	this->addChild(enemy3,4);
	_enemy3Vector.pushBack(enemy3);
	enemy3->enemyFly(enemy3->getEnemyOriginPosition(Size(169,258)));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("big_spaceship_flying.mp3");
}

//移除制定的敌机，这里觉得做得不好，因为还要判断在哪个容器中再删除
void EnemyLayer::removeEnemy(Enemy* enemy)
{
	if(_enemy1Vector.contains(enemy))
		_enemy1Vector.eraseObject(enemy);
	else if(_enemy2Vector.contains(enemy))
		_enemy2Vector.eraseObject(enemy);
	else
		_enemy3Vector.eraseObject(enemy);
}

//设置游戏难度，只要是改变敌机发射的频率
void EnemyLayer::setLevelFactor(float factor)
{
	this->stopEnemy();
	this->startEnemy(factor);
}

void EnemyLayer::startEnemy(float factor)
{
   this->schedule(schedule_selector(EnemyLayer::addEnemy1), factor*5, kRepeatForever, factor*3);
   this->schedule(schedule_selector(EnemyLayer::addEnemy2), factor*15, kRepeatForever, factor*10);
   this->schedule(schedule_selector(EnemyLayer::addEnemy3), factor*30, kRepeatForever, factor*30);
}

void EnemyLayer::stopEnemy()
{
	this->unschedule(schedule_selector(EnemyLayer::addEnemy1));
	this->unschedule(schedule_selector(EnemyLayer::addEnemy2));
	this->unschedule(schedule_selector(EnemyLayer::addEnemy3));
}

//void EnemyLayer::removeAllEnemy()
//{
//     	for(auto enemy : _enemy1Vector)
//	     {
//			 enemy->enemyBlowUp("enemy1DownAnimation");
//	     }
//		_enemy1Vector.clear();
//
//	    for(auto enemy : _enemy2Vector)
//	     {
//	       enemy->enemyBlowUp("enemy2DownAnimation");
//	     }	
//		_enemy2Vector.clear();
//
//		for(auto enemy : _enemy3Vector)
//	     {
//		   enemy->enemyBlowUp("enemy3DownAnimation");
//	     }
//		_enemy3Vector.clear();
//}




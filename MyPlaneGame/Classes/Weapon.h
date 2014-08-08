#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "HeroPlane.h"

typedef enum
{
   Bullet1 = 0,
   Bullet2
}BulletType;

class Weapon : public cocos2d::Layer
{
public:
	Weapon(void);
	~Weapon(void);

	CC_SYNTHESIZE_READONLY(HeroPlane*, _heroPlane, heroPlane);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, _bulletVector, bulletVector);

	CREATE_FUNC(Weapon);
	bool init();

	//添加子弹
	void addBullet(float dt);
	//添加双排子弹
	void addMultiBullet(float dt);
	//移除子弹
	void removeBullet(Bullet* bullet);
	//获取子弹发射位置
	cocos2d::Point getShootPostion();
	//飞机爆炸
	void heroBlowUp();
	//开启单排子弹发射
	void startBullet1Shoot(float dt);
	//停止单排子弹发射
	void stopBullet1Shoot();
	//开启双排子弹发射
	void startBullet2Shoot();
	//停止双排子弹发射
	void stopBullet2Shoot();
	//改变子弹类型
	void changeBullet();
	//暂停触摸
	void pauseTouch();
	//恢复触摸
	void resumeTouch();

	//添加触摸事件
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	cocos2d::EventListenerTouchOneByOne* touchListener;
	BulletType bulletType;

};




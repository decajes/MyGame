#pragma once
#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
	Bullet(void);
	~Bullet(void);
	//重新写create和initWithFrameName,不然不能使用Sprite中的初始化函数
	static Bullet* createBullet(std::string frameName);
	void initBulletWithFrameName(std::string frameName);

	//子弹移动
	void bulletMove(cocos2d::Point origin);
	//移动结束操作
	void moveEnd();
	
};


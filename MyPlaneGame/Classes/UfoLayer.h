#pragma once
#include "cocos2d.h"

class UfoLayer : public cocos2d::Layer
{
public:
	UfoLayer(void);
	~UfoLayer(void);
	CREATE_FUNC(UfoLayer);
	bool init();
	//添加ufo
	void addUfo(float dt);
	//随机获得位置
	cocos2d::Point getRandomPosition(cocos2d::Size size);
	//定义ufo管理容器
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<cocos2d::Sprite*>, _ufoVector, ufoVector);
	//ufo飞行
	void ufoMove(cocos2d::Sprite* ufo, cocos2d::Point pos);
	//飞行结束
	void moveEnd(cocos2d::Sprite* ufo);
	//碰撞处理
	void collision(cocos2d::Sprite* ufo);
	//添加bomb的标志
	void addBombItem();
	//销毁当前所有敌机
	void destroyAllEnemy();
	//更新bomb数目
	void updateBombNum();
	//增加bomb
	void addBombNum();
	//减少bomb
	void subBombNum();
private:
	int m_bombNum;
	cocos2d::Label* bombCount;
};


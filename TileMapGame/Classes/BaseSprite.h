#pragma once
#include "cocos2d.h"

//游戏状态
typedef enum
{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD,
	ACTION_STATE_REMOVE,
}ActionState;

//保存人物的大小信息，actual为以原点的Rect,original为以人物大小左下角的Rect,作用是用于碰撞检测
typedef struct _BoundingBox
{
   cocos2d::Rect actual;
   cocos2d::Rect original;
}BoundingBox;

class BaseSprite : public cocos2d::Sprite
{
public:
	BaseSprite(void);
	~BaseSprite(void);

	//定义运行不种不同状态的动画
	void runIdleAction();
	void runWalkAction();
	void runAttactAction();
	void runHurtAction();
	void runDeadAction();
	//移除精灵
	void removeSprite();

	//定义动作精灵
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pIdleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pWalkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pAttackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pHurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pDeadAction, DeadAction);

	//定义状态变量
	CC_SYNTHESIZE(ActionState, m_curActionState, CurActionState);
	//角色的速度
	CC_SYNTHESIZE(cocos2d::Point, m_fVelocity, Velocity);
	//角色的血量
	CC_SYNTHESIZE(unsigned int, m_hp, HP);
	//角色的攻击力
	CC_SYNTHESIZE(unsigned int, m_attack, Attack);
	//角色的受攻击范围
	CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
	//角色的攻击范围
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);

	//这里自定义setPosition,并更新受攻击和攻击范围
	virtual void setPosition(const cocos2d::Point &position);
	//角色死亡
	virtual void onDead();
	//角色是否存活
	virtual bool isLive();

	//定义死亡后的回调事件
	cocos2d::CallFunc* createDeadCallbackFunc();
	//定义休闲状态下的回调事件
	cocos2d::CallFunc* createIdleCallbackFunc();

	//定义一个无返回值无参数的函数模版，其实相当于函数指针
	std::function<void(void)> onDeadCallback;
	//同上
	std::function<void(void)> attack;

protected:
	//创建一个动画
	static cocos2d::Animation* createAnimation(const char* formatStr, int frameCount, int fps);
	//创建一个boundingbox结构体
	BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
	//更新范围
	void updateBoxes();

private:
	//改变状态
	bool changeState(ActionState actionState);

};




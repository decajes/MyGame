#include "BaseSprite.h"
USING_NS_CC;

//初始化各个变量
BaseSprite::BaseSprite(void):
	m_pIdleAction(NULL),
	m_pWalkAction(NULL),
	m_pAttackAction(NULL),
	m_pHurtAction(NULL),
	m_pDeadAction(NULL),
	m_curActionState(ACTION_STATE_NONE)
{
}

//销毁的时候要把retain的对象release
BaseSprite::~BaseSprite(void)
{
	CC_SAFE_RELEASE_NULL(m_pIdleAction);
	CC_SAFE_RELEASE_NULL(m_pWalkAction);
	CC_SAFE_RELEASE_NULL(m_pAttackAction);
	CC_SAFE_RELEASE_NULL(m_pHurtAction);
	CC_SAFE_RELEASE_NULL(m_pDeadAction);
}

//执行休闲的动作
void BaseSprite::runIdleAction()
{
	if(changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_pIdleAction);
	}
}

//执行行走的动作
void BaseSprite::runWalkAction()
{
	if(changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_pWalkAction);
	}
}

//执行受到攻击的动作
void BaseSprite::runHurtAction()
{
	if(changeState(ACTION_STATE_HURT))
	{
		this->runAction(m_pHurtAction);
	}
}

//执行攻击的动作
void BaseSprite::runAttactAction()
{
	if(changeState(ACTION_STATE_ATTACK))
	{
		this->runAction(m_pAttackAction);
	}
}

//执行死亡的动作
void BaseSprite::runDeadAction()
{
	if(changeState(ACTION_STATE_DEAD))
	{
		this->m_hp = 0;
		this->runAction(m_pDeadAction);
	}
}

//删除精灵
void BaseSprite::removeSprite()
{
	changeState(ACTION_STATE_REMOVE);
	log("BaseSprite::removeSprite m_curActionState = %d", m_curActionState);
}

//创建动画
Animation* BaseSprite::createAnimation(const char* formatStr, int frameCount, int fps)
{
	Vector<SpriteFrame*> pFrames(frameCount);
	for(int i = 0; i < frameCount; ++i)
	{
		const char* frameName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		pFrames.pushBack(pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f/fps);
}

//死亡后回调函数
CallFunc* BaseSprite::createDeadCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(BaseSprite::onDead, this));
}

//休闲状态的回调函数
CallFunc* BaseSprite::createIdleCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(BaseSprite::runIdleAction, this));
}

//死亡
void BaseSprite::onDead()
{
    this->onDeadCallback();
}

//判断角色是否存活
bool BaseSprite::isLive()
{
	if(this->m_curActionState >= ACTION_STATE_DEAD)
	{
	  return false;
	}else{
	  return true;
	}
}

//状态判断的第一个条件的||后面的部分不好理解，回头再来看？？？？
bool BaseSprite::changeState(ActionState actionState)
{
	if((m_curActionState == ACTION_STATE_DEAD && actionState != ACTION_STATE_REMOVE) || m_curActionState == actionState)
	{
	   return false;
	}

	this->stopAllActions();
	this->m_curActionState = actionState;
	if(actionState == ACTION_STATE_REMOVE)
		 return false;
	else 
		 return true;

}

//这个函数返回的结构体包含两个rect,一个用于碰撞检测，以左下角为原点的actual.另一个为original，保存以物体坐下角为原点的rect
BoundingBox BaseSprite::createBoundingBox(Point origin, Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
	boundingBox.actual.size = size;
	return boundingBox;
}

//更新攻击范围和被攻击范围
void BaseSprite::updateBoxes() {
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if(isFlippedX) {
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}else {
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Point(x, this->getPosition().y + m_hitBox.original.origin.y);
    m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}

//设置物体的位置，这里多加一个updateBoxes();
void BaseSprite::setPosition(const Point &position)
{
	Sprite::setPosition(position);
	this->updateBoxes();
}
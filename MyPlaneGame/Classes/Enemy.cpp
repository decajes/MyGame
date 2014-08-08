#include "Enemy.h"
#include "EnemyLayer.h"
USING_NS_CC;

static const Size Enemy1Size = Size(57,43);
static const Size Enemy2Size = Size(69,99);
static const Size Enemy3Size = Size(169,258);
static const int ENDY = -150;

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

Enemy* Enemy::createEnemy()
{
	Enemy* enemy = new Enemy();
	if(enemy)
	{
		enemy->initWithTexture(nullptr, Rect::ZERO);
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::initEnemyWithFrameName(std::string filename)
{
	this->initWithSpriteFrameName(filename);
}


//随机获取初始位置。这里有个问题。到底是运行时直接去get Size 还是直接定义常量好呢？
Point Enemy::getEnemyOriginPosition(Size enemySize)
{
	auto winSize = Director::getInstance()->getWinSize();
	float posX = (float)(rand()%(int(winSize.width - enemySize.width)) + enemySize.width*0.5);
	float posY = winSize.height + enemySize.height;
	return Point(posX, posY);
}

//先随便定义
int Enemy::getSpeed()
{
    return rand()%200+100;
}

//敌机飞行
void Enemy::enemyFly(Point pos)
{
	this->setPosition(pos);
	Point destination = Point(pos.x, ENDY);
	float duration = (pos.y - ENDY)/(getSpeed());
	auto moveTo = MoveTo::create(duration, destination);
	auto flyEnd = CallFunc::create(CC_CALLBACK_0(Enemy::FlyEnd, this));
	this->runAction(Sequence::create(moveTo, flyEnd, NULL));
}

//敌机飞行结束之后的处理
void Enemy::FlyEnd()
{
	EnemyLayer* enemylayer = (EnemyLayer*)this->getParent();
	enemylayer->removeEnemy(this);
	this->removeFromParentAndCleanup(true);
}

//敌机爆炸，传入的参数为爆炸动画的名称
void Enemy::enemyBlowUp(std::string animationName)
{
	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
	auto hide = Hide::create();
	auto callback = CallFunc::create(CC_CALLBACK_0(Enemy::FlyEnd, this));
	this->stopAllActions();
	this->runAction(Sequence::create(animate, hide, callback, NULL));
}

//设置生命值
void Enemy::setLife(int life)
{
   this->m_life = life;
}

//判断敌机是否已经死亡
bool Enemy::isDead()
{
	m_life--;
	if(m_life)
		return false;
	else
		return true;
}
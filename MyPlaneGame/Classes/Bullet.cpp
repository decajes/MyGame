#include "Bullet.h"
#include "Weapon.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

const int END_Y = 875; //子弹的结束位置，按照屏幕高度+子弹高度计算（852 + 21）
const int speed = 300; //设置子弹的速度

Bullet::Bullet(void)
{
}

Bullet::~Bullet(void)
{
}


Bullet* Bullet::createBullet(std::string frameName)
{
	Bullet* bullet = new Bullet();
	if(bullet)
	{
		bullet->initWithSpriteFrameName(frameName);
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::initBulletWithFrameName(std::string frameName)
{
	this->initWithSpriteFrameName(frameName);
}

//子弹的飞行
void Bullet::bulletMove(Point origin)
{
	//设置子弹的飞行的参数
	this->setPosition(origin);
	auto destination = Point(origin.x, END_Y);
	float duration = (END_Y - origin.y)/speed;

	//创建移动动作和动作完成后的回调动作
	auto moveTo = MoveTo::create(duration, destination);
	auto moveEnd = CallFunc::create(CC_CALLBACK_0(Bullet::moveEnd, this));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");
	this->runAction(Sequence::create(moveTo, moveEnd, NULL));
}

//子弹结束的处理
void Bullet::moveEnd()
{
	Weapon* weapon = (Weapon*)this->getParent();
	weapon->removeBullet(this);
}



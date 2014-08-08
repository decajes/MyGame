#include "Weapon.h"
USING_NS_CC;

static const int PlaneWidth = 102;
static const int PlaneHeight = 126;

Weapon::Weapon(void)
{
}


Weapon::~Weapon(void)
{
}

bool Weapon::init()
{
   do
   {
	   //添加飞机
	   _heroPlane = HeroPlane::getInstance();
	   this->addChild(_heroPlane);

	   //延迟2秒发射子弹
	   startBullet1Shoot(2.0f);

	   //添加触摸事件，并添加到分发器中去
	   touchListener = EventListenerTouchOneByOne::create();
	   touchListener->setSwallowTouches(true);
	   touchListener->onTouchBegan = CC_CALLBACK_2(Weapon::onTouchBegan, this);
	   touchListener->onTouchMoved = CC_CALLBACK_2(Weapon::onTouchMoved, this);
	   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, _heroPlane);

	   return true;
   }while(0);

   return false;
}

//添加子弹
void Weapon::addBullet(float dt)
{
	Bullet* bullet = Bullet::createBullet("bullet1.png"); //这个可以使用批次渲染，慢慢改善
	this->addChild(bullet, 1);
	//添加到子弹管理器中
	_bulletVector.pushBack(bullet);
	//获得初始位发射
	bullet->bulletMove(getShootPostion());
}

//添加双子弹发射，同单子弹发射一样，就是两个单排子弹
void Weapon::addMultiBullet(float dt)
{

	Bullet* bulletLeft = Bullet::createBullet("bullet2.png");
	Bullet* bulletRight = Bullet::createBullet("bullet2.png");
	this->addChild(bulletLeft,1);
	this->addChild(bulletRight,1);
	_bulletVector.pushBack(bulletLeft);
	_bulletVector.pushBack(bulletRight);
	bulletLeft->bulletMove(ccpSub(getShootPostion(), Point(7, 0)));
	bulletRight->bulletMove(ccpAdd(getShootPostion(), Point(7, 0)));
}

//获得发射位置，即是返回飞机头的位置
Point Weapon::getShootPostion()
{
	auto pos = _heroPlane->getHero()->getPosition();
	auto shootPos = Point(pos.x, pos.y+PlaneHeight/2);
	return shootPos;
}

//移除子弹，还要注意从子弹管理容器中除去
void Weapon::removeBullet(Bullet* bullet)
{
	_bulletVector.eraseObject(bullet);
	this->removeChild(bullet, true);
}

//飞机爆炸
void Weapon::heroBlowUp()
{
	this->unscheduleAllSelectors();//停止子弹发射
	_eventDispatcher->removeEventListener(touchListener);//停止触摸监听
	_heroPlane->blowUp();//飞机爆炸
}

//单排子弹的发射，用定时器实现，传入参数为延迟时间dt
void Weapon::startBullet1Shoot(float dt)
{
	this->bulletType = Bullet1;
	this->schedule(schedule_selector(Weapon::addBullet), 0.3f, kRepeatForever, dt);
}

//单排子弹的停止发射，停止发射器
void Weapon::stopBullet1Shoot()
{
	this->unschedule(schedule_selector(Weapon::addBullet));
}

//双排子弹的发射
void Weapon::startBullet2Shoot()
{
    this->bulletType = Bullet2;
	this->schedule(schedule_selector(Weapon::addMultiBullet), 0.3f, 20, 0);
}

//双排子弹的停止发射
void Weapon::stopBullet2Shoot()
{
	this->unschedule(schedule_selector(Weapon::addMultiBullet));
}

//改变子弹的类型，用于获得双排子弹ufo的时候进行切换
//先停止单排的发射，然后延时启动单排的发射，并执行有次数限制的双排发射
//这里还要注意到双排子弹发射过程中又获得双排子弹的时候的处理
void Weapon::changeBullet()
{
	this->stopBullet1Shoot(); 
	if(this->bulletType == Bullet2)
	{
	  this->stopBullet2Shoot();
	}
	this->startBullet1Shoot(6.5f);
	this->startBullet2Shoot();
	
}

//触摸开始事件
bool Weapon::onTouchBegan(Touch* touch, Event* event)
{
	//获得飞机的触摸范围
	auto node = dynamic_cast<HeroPlane*>(event->getCurrentTarget());
	Rect rect = node->getHero()->getBoundingBox();
	//扩大触摸点的范围
	Rect touchRect = Rect(rect.origin.x-5, rect.origin.y-5, rect.size.width+10, rect.size.height+10);
	Point point = touch->getLocation();
	//判断触摸点是否在触摸允许范围内
	if(touchRect.containsPoint(point))
	{
	   return true;
	}
	return false;
}

//触摸移动事件
void Weapon::onTouchMoved(Touch* touch, Event* event)
{
    auto node = dynamic_cast<HeroPlane*>(event->getCurrentTarget());
	Size winSize = CCDirector::getInstance()->getWinSize();

	//设置范围
	auto point = node->getHero()->getPosition()+touch->getDelta();
	point.x = MAX(point.x , PlaneWidth*0.4);
	point.x = MIN(point.x , (winSize.width - PlaneWidth*0.4));
	point.y = MAX(point.y , PlaneHeight*0.4);
	point.y = MIN(point.y , (winSize.height - PlaneHeight*0.4));

	node->getHero()->setPosition(point);
}

//暂停触摸,用于控制游戏暂停
void Weapon::pauseTouch()
{
   _eventDispatcher->pauseEventListenersForTarget(_heroPlane);
}

//恢复触摸，用于控制恢复游戏
void Weapon::resumeTouch()
{
	_eventDispatcher->resumeEventListenersForTarget(_heroPlane);
}


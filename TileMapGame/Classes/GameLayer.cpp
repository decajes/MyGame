#include "GameLayer.h"
#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


GameLayer::GameLayer(void)
	:m_tileMap(NULL),
	m_pSpriteNodes(NULL),
	m_pHero(NULL),
	m_pEnemyVector(NULL),
	m_pRemoveVecotr(NULL),
	m_pBlood(NULL),
	m_pBloodBg(NULL)
{
}


GameLayer::~GameLayer(void)
{
	 m_tileMap = NULL;
	//_background = NULL;
}

bool GameLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_origin = Director::getInstance()->getVisibleOrigin();
	this->m_fScreenWidth = visibleSize.width;
	this->m_fScreenHeight = visibleSize.height;

	loadVoice();

	//预处理一下资源载入
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
	m_pSpriteNodes = SpriteBatchNode::create("pd_sprites.pvr.ccz");
	this->addChild(m_pSpriteNodes);
	
	//加载地图
	m_tileMap = TMXTiledMap::create("pd_tilemap.tmx");
	this->addChild(m_tileMap, -10);
	Size tileSize = m_tileMap->getTileSize();
	m_fTileWidth = tileSize.width;
	m_fTileHeight = tileSize.height;

	//添加主角
	m_pHero = Hero::create();
	m_pHero->setPosition(m_origin + Point(100, 100));
	m_pHero->runIdleAction();
	m_pHero->setZOrder(m_fScreenHeight - m_pHero->getPositionY());
	m_pHero->setAttack(5);
	m_pHero->setHP(100);
	m_pSpriteNodes->addChild(m_pHero);
	m_pHero->onDeadCallback = CC_CALLBACK_0(GameLayer::onHeroDead, this, m_pHero);
	m_pHero->attack = CC_CALLBACK_0(GameLayer::onHeroAttack, this);
	m_pHero->stop = CC_CALLBACK_0(GameLayer::onHeroStop, this);
	m_pHero->walk = CC_CALLBACK_2(GameLayer::onHeroWalk, this);

	m_pEnemyVector = Vector<BaseSprite*> (MIN_ENEMY_COUNT);
	for(int i = 0; i < MIN_ENEMY_COUNT; ++ i)
	{
		this->addEnemy();
	}

	this->m_pBlood = ProgressTimer::create(Sprite::create("blood.png"));
	this->m_pBlood->setType(ProgressTimer::Type::BAR);
	this->m_pBlood->setMidpoint(Point(0, 0));
	this->m_pBlood->setBarChangeRate(Point(1, 0));
	this->m_pBlood->setAnchorPoint(Point(0, 1));
	this->m_pBlood->setPosition(m_origin + Point(2, m_fScreenHeight - 10));
	this->m_pBlood->setPercentage(100);

	this->m_pBloodBg = ProgressTimer::create(Sprite::create("bloodBg.png"));
	this->m_pBloodBg->setType(ProgressTimer::Type::BAR);
	this->m_pBloodBg->setMidpoint(Point(0, 0));
	this->m_pBloodBg->setBarChangeRate(Point(1, 0));
	this->m_pBloodBg->setAnchorPoint(Point(0, 1));
	this->m_pBloodBg->setPosition(this->m_pBlood->getPosition());
	this->m_pBloodBg->setPercentage(100);

	this->addChild(m_pBloodBg, 100);
	this->addChild(m_pBlood, 100);

	m_pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameLayer::exitApp, this));
	m_pCloseItem->setPosition(this->m_origin + Point(visibleSize) - Point(m_pCloseItem->getContentSize() / 2));
	auto menu = Menu::create(m_pCloseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	this->scheduleUpdate();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hero_talk.mp3");
	return true;
}

void GameLayer::exitApp(Ref* ref)
{
	Director::getInstance()->end();
}

void GameLayer::loadVoice()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background-music-aac.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_hit0.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_hit1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_herodeath.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_botdeath.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hero_talk.mp3");
}

void GameLayer::onHeroWalk(Point direction, float distance)
{
	m_pHero->setFlippedX(direction.x < 0 ? true : false);
	m_pHero->runWalkAction();
	Point velocity = direction * (distance < 78 ? 1 : 3);
	m_pHero->setVelocity(velocity);
}

void GameLayer::onHeroAttack()
{
	m_pHero->runAttactAction();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pd_hit0.mp3");
	if(m_pHero->getCurActionState() == ACTION_STATE_ATTACK)
	{
		for(auto enemyObj : m_pEnemyVector)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(enemyObj);
			if(enemy->getCurActionState() >= ACTION_STATE_DEAD)
			{
				continue;
			}
			if(fabsf(m_pHero->getPositionY() - enemy->getPositionY()) < 10)
			{
				BoundingBox heroHitBox = m_pHero->getHitBox();
				BoundingBox enemyBodyBox = enemy->getBodyBox();

				if(collisionDetection(heroHitBox, enemyBodyBox))
				{
					int damage = m_pHero->getAttack();
					enemy->runHurtAction();
					enemy->setHP(enemy->getHP() - damage);
					
					if(enemy->getHP() <= 0)
					{
						enemy->runDeadAction();
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pd_botdeath.mp3");
					}
				}
			}
		}
	}

}

void GameLayer::onHeroStop()
{
	m_pHero->runIdleAction();
}

void GameLayer::onHeroDead(BaseSprite *target)
{
	if(m_pHero->getCurActionState() == ACTION_STATE_DEAD)
	{
		target->removeSprite();
		this->m_pBlood->setPercentage(0);
		this->gameOver();
	}
   
}

void GameLayer::update(float dt)
{
	 this->updateHero(dt);
	 //this->updateEnemies(dt);
}

void GameLayer::updateHero(float dt)
{
	if(m_pHero->getCurActionState() == ACTION_STATE_WALK)
	{
		float halfHeroFrameHeight = (m_pHero->getDisplayFrame()->getRect().size.height) / 2;
		Point expectP = m_pHero->getPosition() + m_pHero->getVelocity();
		Point actualP = expectP;

		if(expectP.y < halfHeroFrameHeight || expectP.y > m_fTileHeight*3 + halfHeroFrameHeight)
		{
			actualP.y = m_pHero->getPositionY();
		}

		float mapWidth = m_tileMap->getContentSize ().width;
		float halfWinWidth = m_fScreenWidth / 2;
		float halfHeroFrameWidth = (m_pHero->getDisplayFrame()->getRect().size.width) / 2;
		
		if(expectP.x > halfWinWidth && expectP.x <= (mapWidth - halfWinWidth))
		{
			//地图向左移动，这样看起来就好像人相对于地图在向右移动，同时血条也向右移动
			this->setPositionX(this->getPositionX() - m_pHero->getVelocity().x);
			this->m_pBlood->setPositionX(this->m_pBlood->getPositionX() + m_pHero->getVelocity().x);
			this->m_pBloodBg->setPositionX(this->m_pBloodBg->getPositionX() + m_pHero->getVelocity().x);
		}else if(expectP.x < halfHeroFrameWidth || expectP.x >= mapWidth - halfHeroFrameWidth)
        {
            actualP.x = m_pHero->getPositionX();
         }
           m_pHero->setPosition(actualP);
           m_pHero->setZOrder(m_fScreenHeight - m_pHero->getPositionY());
	}
}

void GameLayer::addEnemy()
{
	auto winSize = Director::getInstance()->getWinSize();
	Point location = Point::ZERO;
	Enemy *pEnemy = Enemy::create();

	float halfEnemyFrameHeight = (pEnemy->getDisplayFrame()->getRect().size.width) / 2;
	float heroPosX = m_pHero->getPositionX();
	float halfWinWidth = winSize.width / 2;

	while(fabs(heroPosX - location.x) < 150)
	{
		if(heroPosX < halfWinWidth)
		{
			location.x = m_pHero->getPositionX() + CCRANDOM_0_1() * halfWinWidth;
		}else if(heroPosX > (m_tileMap->getMapSize().width * m_fTileWidth - halfWinWidth)){
			location.x = m_pHero->getPositionX() - CCRANDOM_0_1() * halfWinWidth;
		}else{
			location.x = m_pHero->getPositionX() +CCRANDOM_MINUS1_1() * halfWinWidth;
		}
	}

	float maxY = m_fTileHeight * 3 + halfEnemyFrameHeight;
	location.y = CCRANDOM_0_1() * maxY;
	if(location.y < halfEnemyFrameHeight)
	{
		location.y = halfEnemyFrameHeight;
	}

	pEnemy->attack = CC_CALLBACK_0(GameLayer::onEnemyAttack, this, pEnemy);
	pEnemy->onDeadCallback = CC_CALLBACK_0(GameLayer::onEnemyDead, this, pEnemy);
	pEnemy->setPosition(m_origin + location);
	pEnemy->setZOrder(m_fScreenHeight - pEnemy->getPositionY());
	pEnemy->runIdleAction();
	pEnemy->setAttack(5);
	pEnemy->setHP(30);
	pEnemy->setVelocity(Point(0.5f, 0.5f));//这个速度有什么用呢？
	pEnemy->setEyeArea(200);
	pEnemy->setAttackArea(25);
	m_pEnemyVector.pushBack(pEnemy);
	m_pSpriteNodes->addChild(pEnemy);
}

void GameLayer::updateEnemies(float dt)
{
	Point distance = Point::ZERO;

	Point heroLocation = m_pHero->getPosition();

	for(auto enemy : m_pEnemyVector)
	{
		Enemy* pEnemy = dynamic_cast<Enemy*>(enemy);
		pEnemy->execute(heroLocation, m_pHero->getDisplayFrame()->getRect().size.width);
	    
		/*if(pEnemy->getHP() <= 0)
		{
		  	m_pSpriteNodes->removeChild(enemy, true);
			m_pEnemyVector.eraseObject(enemy);
			break;
		}*/
		if(pEnemy->getCurActionState() == ACTION_STATE_REMOVE)
		{
		    //m_pSpriteNodes->removeChild(enemy, true);
			m_pRemoveVecotr.pushBack(pEnemy);
			continue;
		}

		if(pEnemy->getCurActionState() == ACTION_STATE_WALK)
		{
			Point location = pEnemy->getPosition();
			Point direction = pEnemy->getMoveDirection();

			Point expect = location + direction;
			float halfEnemyFrameheight = (pEnemy->getDisplayFrame()->getRect().size.height)/2;

			if(expect.y < halfEnemyFrameheight || expect.y > (m_fTileHeight * 3 + halfEnemyFrameheight))
			{
			   direction.y = 0;
			}

			pEnemy->setFlippedX(direction.x < 0 ? true : false);
			pEnemy->setPosition(location + direction);
			pEnemy->setZOrder(pEnemy->getPositionY());
		}
	}	
 
	if(!m_pRemoveVecotr.empty())
	{
		for(auto removeObj : m_pRemoveVecotr)
		{
			Enemy *removeEnemy = dynamic_cast<Enemy*>(removeObj);
			removeEnemy->removeFromParentAndCleanup(true);
			m_pEnemyVector.eraseObject(removeEnemy);
			m_pEnemyVector.eraseObject(removeEnemy);
		}
	}
}

void GameLayer::onEnemyDead(BaseSprite *target)
{
   target->removeSprite();
}

void GameLayer::onEnemyAttack(BaseSprite *pSprite)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pd_hit1.mp3");
	for(auto enemyObj : m_pEnemyVector)
	{
		Enemy *enemy = dynamic_cast<Enemy*>(enemyObj);
		if(enemy->getCurActionState() == ACTION_STATE_ATTACK)
		{
			enemy->setPositionY(m_pHero->getPositionY());
			BoundingBox heroBodyBox = m_pHero->getBodyBox();
			BoundingBox enemyHitBox = enemy->getHitBox();

			if(collisionDetection(enemyHitBox, heroBodyBox))
			{
				int damage = enemy->getAttack();
				if(enemy->isFlippedX() == m_pHero->isFlippedX())
				{
					m_pHero->setFlippedX(!m_pHero->isFlippedX());
				}
				m_pHero->runHurtAction();
				m_pHero->setHP(m_pHero->getHP() - damage);

				if(m_pHero->getHP() <= 0)
				{
					this->unscheduleUpdate();/////////////
					m_pHero->runDeadAction();
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pd_herodeath.mp3");
				}

				this->m_pBlood->setPercentage( (m_pHero->getHP() / 100.0f) * 100);
			}
		}
	}
}

bool GameLayer::collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox)
{
	Rect hitRect = hitBox.actual;
	Rect bodyRect = bodyBox.actual;
	if(hitRect.intersectsRect(bodyRect))
	{
	   return true;
	}else{
	   return false;
	}
}

void GameLayer::gameOver()
{
	
	//Scene* gameOverScene = TransitionCrossFade::create(1.0f, GameOverLayer::createScene());
	Scene* gameOverScene = GameOverLayer::createScene();
	Director::getInstance()->replaceScene(gameOverScene);
}
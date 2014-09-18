#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Enemy.h"

static const int MIN_ENEMY_COUNT = 5;

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer(void);
	~GameLayer(void);
	bool init();
	CREATE_FUNC(GameLayer);
	cocos2d::TMXTiledMap *m_tileMap;

	CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);
	float m_fScreenWidth;
	float m_fScreenHeight;
	cocos2d::Point m_origin;
	cocos2d::SpriteBatchNode *m_pSpriteNodes;

	void onHeroWalk(cocos2d::Point direction, float distance);
	void onHeroAttack();
	void onHeroStop();
	void onHeroDead(BaseSprite* target);
	void update(float dt);
	void updateHero(float dt);

	float m_fTileWidth;
	float m_fTileHeight;

	void updateEnemies(float dt);
	void addEnemy();
	void onEnemyAttack(BaseSprite *pSprite);
	void onEnemyDead(BaseSprite *target);
	cocos2d::Vector<BaseSprite*>m_pEnemyVector;
	cocos2d::Vector<BaseSprite*>m_pRemoveVecotr;

	bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

	cocos2d::ProgressTimer *m_pBlood;
	cocos2d::ProgressTimer *m_pBloodBg;
	cocos2d::MenuItemImage *m_pCloseItem;

	void exitApp(cocos2d::Ref* pSender);

	void loadVoice();

	void gameOver();
};


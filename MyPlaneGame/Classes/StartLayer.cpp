#include "StartLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

StartLayer::StartLayer(void)
{
}


StartLayer::~StartLayer(void)
{
}

Scene* StartLayer::scene()
{
   Scene* startScene = Scene::create();
   StartLayer* startLayer = StartLayer::create();
   startScene->addChild(startLayer);
   return startScene;
}

bool StartLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   //预处理数据
	   preLoadResource();

	   //添加加载画面背景
	   Sprite* background = Sprite::createWithSpriteFrameName("background.png");
	   background->setAnchorPoint(Point::ZERO);
	   background->setPosition(Point::ZERO);
	   this->addChild(background);

	   auto winSize = Director::getInstance()->getWinSize();

	   //添加版本信息
	   auto copyRightSprite = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	   copyRightSprite->setPosition(winSize.width*0.5, winSize.height*0.6);
	   this->addChild(copyRightSprite);

	   //执行加载动画
	   Sprite* start = Sprite::create();
	   auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("startAnimation"));
	   auto callback = CallFunc::create(CC_CALLBACK_0(StartLayer::transition, this));
	   start->setPosition(winSize.width*0.5, winSize.height*0.4);
	   this->addChild(start);
	   start->runAction(Sequence::create(animate, callback, NULL));


	   return true;
   }while(0);
       
       return false;
}

void StartLayer::preLoadResource()
{
  	//帧缓存初始化
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist");

	//缓存飞机动画
	Animation* heroAnimation = Animation::create();
	heroAnimation->setDelayPerUnit(0.2f);
	heroAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	heroAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	AnimationCache::getInstance()->addAnimation(heroAnimation,"heroAnimation");

	//敌机3的飞行动画
	Animation* enemy3Animation = Animation::create();
	enemy3Animation->setDelayPerUnit(0.2f);
	enemy3Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
	enemy3Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	AnimationCache::getInstance()->addAnimation(enemy3Animation,"enemy3Animation");

	//英雄飞机的爆炸动画
	Animation* heroBlowupAnimation = Animation::create();
	heroBlowupAnimation->setDelayPerUnit(0.2f);
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));
	AnimationCache::getInstance()->addAnimation(heroBlowupAnimation,"heroBlowupAnimation");
    
	//敌机1的爆炸动画
	Animation* enemy1DownAnimation = Animation::create();
	enemy1DownAnimation->setDelayPerUnit(0.05f);
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
	AnimationCache::getInstance()->addAnimation(enemy1DownAnimation, "enemy1DownAnimation");

	//敌机2的爆炸动画
	Animation* enemy2DownAnimation = Animation::create();
	enemy2DownAnimation->setDelayPerUnit(0.05f);
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
	AnimationCache::getInstance()->addAnimation(enemy2DownAnimation, "enemy2DownAnimation"); 

	//敌机3的爆炸动画
	Animation* enemy3DownAnimation = Animation::create();
	enemy3DownAnimation->setDelayPerUnit(0.05f);
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
	AnimationCache::getInstance()->addAnimation(enemy3DownAnimation, "enemy3DownAnimation"); 

	//初始化界面动画
	Animation* startAnimation = Animation::create();
	startAnimation->setDelayPerUnit(0.5);
	startAnimation->setLoops(2);
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
	AnimationCache::getInstance()->addAnimation(startAnimation, "startAnimation");

	//初始化用户数据，这里只有一个最高记录
	UserData::getInstance()->saveUserData("beet_score", 0);

	//预加载声音文件
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
	//SimpleAudioEngine::getInstance()->preloadEffect("out.porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
}

//场景转换
void StartLayer::transition()
{
	Scene* gameScene = TransitionSlideInR::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameScene);
}

#include "WelcomeLayer.h"
#include "BackgroundLayer.h"
#include "bird.h"
#include "GameScene.h"
USING_NS_CC;

WelcomeLayer::WelcomeLayer(void)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

Scene* WelcomeLayer::createScene()
{
	Scene* scene = Scene::create();
	WelcomeLayer* layer = new WelcomeLayer();
	layer->init();
	scene->addChild(layer);
    return scene;
}

bool WelcomeLayer::init()
{  
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   Size winSize = Director::getInstance()->getWinSize();

	   BackgroundLayer* background = BackgroundLayer::create();
	   this->addChild(background);

	   auto titleSprite = Sprite::createWithSpriteFrameName("title.png");
	   titleSprite->setPosition(Point(winSize.width*0.5, winSize.height*0.75));
	   this->addChild(titleSprite);

	   bird* mybird = bird::getInstance();
	   mybird->setPosition(Point(winSize.width*0.5, winSize.height*0.6));
	   this->addChild(mybird);

	   auto copyRightSprite = Sprite::createWithSpriteFrameName("copyright.png");
	   copyRightSprite->setPosition(Point(winSize.width*0.5, winSize.height*0.45));
	   this->addChild(copyRightSprite);


	   auto startButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("start.png"),Sprite::createWithSpriteFrameName("start.png"),NULL,CC_CALLBACK_1(WelcomeLayer::startCallBack, this));
	   auto rateButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("rate.png"),Sprite::createWithSpriteFrameName("rate.png"));
	   auto menu = Menu::create(startButton, rateButton, NULL);
	   menu->alignItemsHorizontallyWithPadding(50);
	   //menu->alignItemsVerticallyWithPadding(50);
	   menu->setPosition(Point(winSize.width*0.5, winSize.height*0.3));
	   this->addChild(menu, 2);

	     //create the land sprite, because the land need to scroll, so here create two land sprite to replace
	   land1 = Sprite::createWithSpriteFrameName("land.png");
	   land1->setAnchorPoint(Point::ZERO);
	   land1->setPosition(Point::ZERO);
	   land1->getTexture()->setAliasTexParameters();
	   this->addChild(land1);

	   land2 = Sprite::createWithSpriteFrameName("land.png");
	   land2->setAnchorPoint(Point::ZERO);
	   land2->setPosition(Point(land1->getContentSize().width-4.0f, 0));
	   land2->getTexture()->setAliasTexParameters();
	   this->addChild(land2);

	   this->schedule(schedule_selector(WelcomeLayer::landMove),0.01f);

	   return true;
   }while(0);
       return false;
}

void WelcomeLayer::landMove(float dt)
{
    //move the land
	land1->setPositionX(land1->getPosition().x-1.0f);
	land2->setPositionX(land1->getPosition().x + land1->getContentSize().width-4.0f);
	if(land2->getPositionX() == 0)
	{
		land1->setPosition(Point::ZERO);
	}
}

void WelcomeLayer::startCallBack(Object* psender)
{
	bird::getInstance()->releaseBrid();
	Scene* gameScene = GameScene::create();
	TransitionScene* transition = TransitionFade::create(1.0f, gameScene);
	Director::getInstance()->replaceScene(transition);
}
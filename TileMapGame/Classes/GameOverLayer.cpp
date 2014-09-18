#include "GameOverLayer.h"
#include "GameScene.h"
USING_NS_CC;

GameOverLayer::GameOverLayer(void)
	:m_pLabel(NULL)
{
}


GameOverLayer::~GameOverLayer(void)
{

}

bool GameOverLayer::init()
{
    do
	{
		CC_BREAK_IF(!LayerColor::initWithColor(Color4B(255, 255, 255, 255)));

		auto winSize = Director::getInstance()->getWinSize();
		this->m_pLabel = Label::createWithSystemFont("Game Over!!", "Artial", 32);
		this->m_pLabel->setPosition(Point(winSize.width*0.5, winSize.height*0.5));
		this->m_pLabel->setColor(Color3B(0, 0, 0));

		this->addChild(this->m_pLabel);
		this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(GameOverLayer::restartGame, this)), NULL));

	return true;
	}while(0);
	return false;
}

Scene* GameOverLayer::createScene()
{
   auto scene = Scene::create();
   auto layer = GameOverLayer::create();
   scene->addChild(layer);
   return scene;
}

void GameOverLayer::restartGame()
{
 	Scene* gameScene = TransitionCrossFade::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameScene);
}
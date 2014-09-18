#pragma once
#include "cocos2d.h"
class GameOverLayer : public cocos2d::LayerColor
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameOverLayer);

	void restartGame();
	bool init();

	CC_SYNTHESIZE_READONLY(cocos2d::Label*, m_pLabel, GameOverLabel);
};


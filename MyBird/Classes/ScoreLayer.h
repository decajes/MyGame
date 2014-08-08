#pragma once
#include "cocos2d.h"
#include "GameLayer.h"

class ScoreLayer : public cocos2d::Layer,public ScoreDelegator 
{
public:
	ScoreLayer(void);
	~ScoreLayer(void);

	CREATE_FUNC(ScoreLayer);
	bool init();
	void showCurrentScore(int score);
	void showGameOver(int score);

private:
	cocos2d::Vector<cocos2d::SpriteFrame*> numberVector;
	cocos2d::Vector<cocos2d::SpriteFrame*> counterVector;
	cocos2d::Node* scoreNode;
	int iterator;
	int numberPlace;
	int finalScore;
	int bestScore;
	int counter;
	bool getNewRecord;

	cocos2d::Sprite* scoreSprite;
	cocos2d::Sprite* bestSprite;
	cocos2d::Sprite* numberSprite;
	cocos2d::Sprite* counterPanel;
	cocos2d::Menu* menu;
	cocos2d::Sprite* gameOverSprite;
	cocos2d::Sprite* medalSprite;
	void restartCallBack(cocos2d::Object* psender);
	void showMenu();
	void showScore();
	void showGameOverSprite();
	void showCounterPanel();
	void countScore(float dt);
	void showBestScore();
	void showMedal();
	void showNewSprite();
	void showOther();
};


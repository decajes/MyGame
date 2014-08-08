#pragma once
#include "cocos2d.h"
#include "bird.h"
#include "Pipe.h"
#include "TouchLayer.h"

enum GameStatus
{
  GAME_READY = 0,
  GAME_START
};


class ScoreDelegator
{
public:
	virtual void showCurrentScore(int score)=0;
	virtual void showGameOver(int score) = 0;
};

class GameLayer : public cocos2d::Layer,public TouchDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);
	bool init();
	CC_SYNTHESIZE_READONLY(bird*, mybird, myBird);
	CC_SYNTHESIZE(ScoreDelegator*, _scoreDelegator, scoreDelegator);

	void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
	void onTouch();
	void update(float dt);
	

private:
	cocos2d::Sprite* land1;
	cocos2d::Sprite* land2;
	cocos2d::Sprite* getReady;
	cocos2d::Sprite* tapToStart;
	cocos2d::Vector<Pipe*> pipeVector;
	cocos2d::PhysicsWorld* m_world;
	int score;
	GameStatus gameStatus;

	void landMove(float dt);
	float getRandomY();
	bool onContactBegin(cocos2d::PhysicsContact& contact); 	
	void rotateBird();
	void updateScore();
	void gameOver();
	void createPipe();
};


#include "GameAudio.h"
using namespace CocosDenshion;
static GameAudio* _gameAudio = NULL;

GameAudio::GameAudio(void)
{
}


GameAudio::~GameAudio(void)
{
}

GameAudio* GameAudio::getInstance()
{
	if(_gameAudio == NULL)
	{
		_gameAudio = new GameAudio();
		_gameAudio->init();
	}

	return _gameAudio;
}

bool GameAudio::init()
{
	do
	{
		this->preloadEffect("sfx_die.mp3");
		this->preloadEffect("sfx_hit.mp3");
		this->preloadEffect("sfx_point.mp3");
		this->preloadEffect("sfx_swooshing.mp3");
		this->preloadEffect("sfx_wing.mp3");
		return true;
	}while(0);
	    return false;
}
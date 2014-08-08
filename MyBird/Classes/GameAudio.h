#pragma once
#include "SimpleAudioEngine.h"
class GameAudio : public CocosDenshion::SimpleAudioEngine
{
public:
	GameAudio(void);
	~GameAudio(void);

	static GameAudio* getInstance();
	bool init();
};


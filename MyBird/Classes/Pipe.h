#pragma once
#include "cocos2d.h"



class Pipe : public cocos2d::Node
{
public:
	Pipe(void);
	~Pipe(void);

	CREATE_FUNC(Pipe);
	bool init();
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, pipeDown, PipeDown);
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, pipeUp, PipeUp);
};


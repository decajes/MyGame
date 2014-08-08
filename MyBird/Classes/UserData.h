#pragma once
#include "cocos2d.h"

class UserData : public cocos2d::Object
{
public:
	UserData(void);
	~UserData(void);

	static UserData* getInstance();
	bool init();

	void saveUserData(const char* key, int value);
	int readUserData(const char* key);

};


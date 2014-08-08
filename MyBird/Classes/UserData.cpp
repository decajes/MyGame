#include "UserData.h"
USING_NS_CC;

static UserData* _userData = NULL;

UserData::UserData(void)
{
}


UserData::~UserData(void)
{
}

UserData* UserData::getInstance()
{
	if(_userData == NULL)
	{
	   _userData = new UserData();
	   _userData->init();
	}
  
	return _userData;
}

bool UserData::init()
{
   return true;
}

void UserData::saveUserData(const char* key, int value)
{
	UserDefault::getInstance()->setIntegerForKey(key, value);
}

int UserData::readUserData(const char* key)
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}

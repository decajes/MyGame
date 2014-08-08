#include "BackgroundLayer.h"
USING_NS_CC;

BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{ 
   do
   {
	   CC_BREAK_IF(!Layer::init());
	   
	   //calulate the current time, for deciding to use the day or night background image
	  time_t t= time(NULL);
	   tm* nowtime = localtime(&t);
	   int cur_hour = nowtime->tm_hour;

	   if(cur_hour > 6 && cur_hour < 18)
	   {
		   background = Sprite::createWithSpriteFrameName("day_background.png");
	   }
	   else
	   {
		   background = Sprite::createWithSpriteFrameName("night_background.png");
	   }

	   //set the background sprite's property and add to the layer
	   background->setAnchorPoint(Point::ZERO);
	   background->setPosition(Point::ZERO);
	   this->addChild(background);

	   return true;
   }while(0);

   return false;

}



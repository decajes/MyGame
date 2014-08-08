#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "StartLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("mybird");
		//glview->setFrameSize(288, 512);    //设置窗体的大小
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(288, 512, ResolutionPolicy::SHOW_ALL);   //设置游戏界面的大小
    // set the resource directory
	std::vector<std::string> searchPath;
	searchPath.push_back("ui");
	searchPath.push_back("sounds");
	FileUtils::getInstance()->setSearchResolutionsOrder(searchPath);
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = StartLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

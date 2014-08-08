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
        glview = GLView::create("MyPlaneGame");
        director->setOpenGLView(glview);
		glview->setFrameSize(320,480);//设置win32的窗口大小
    }
	//自适应屏幕
	glview->setDesignResolutionSize(480, 852, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

	//set the resource path
	this->setResourcePath();

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = StartLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

//设置目录路径
void AppDelegate::setResourcePath()
{
	std::vector<std::string> resourcePath;
	resourcePath.push_back("ui");
	resourcePath.push_back("sounds");
	resourcePath.push_back("fonts");
	FileUtils::getInstance()->setSearchResolutionsOrder(resourcePath);
}

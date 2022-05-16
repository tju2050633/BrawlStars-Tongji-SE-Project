#include "cocos2d.h"
#include "AppDelegate.h"
#include "Scene/OpeningAnimation.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1

/*杩欒竟鏈変�?�娈甸煶棰戝�煎叆锛岃�?�璐�audio�?ㄥ垎鐨勫悓瀛﹀�圭収鐫�?�?嬩�?�涓�?�?庝箞鍋�*/
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

/*灏哄��*/
static cocos2d::Size designResolutionSize = cocos2d::Size(960, 640);    /*杩欏洓椤瑰彲鑳介渶瑕佷慨鏀�?*/
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

/*鏋勯�?�? 鏋愭�?*/
AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#endif  /*杩欓噷闅忛煶棰戞湁鎵�?涓嶅�?*/
}

/*glContextAttrs 鏆傛椂涓嶇��?*/

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
}

/*瀹�?���?�? 鏆傛椂涓嶇��?*/

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

/*鍒濆��??�?*/

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director

	/*鑾峰彇GLView*/

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("BrawlStars", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("BrawlStars");
#endif
		director->setOpenGLView(glview);
	}

	/*璁剧疆FPS*/

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	/*璁剧疆design resolution*/

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	auto frameSize = glview->getFrameSize();
	// if the frame's height is larger than the height of medium size.

	/*璁剧疆瑙嗙獥灏哄��*/

	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}

	register_all_packages();

	/*鍒涘缓�??�?鍦哄姩鐢籗cene锛岃繍琛屼�??*/

	// create a scene. it's an autorelease object
	auto scene = OpeningAnimation::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

/*绋�??�?杩涘叆鑳屾櫙锛岄渶瑕佹帶鍒堕煶棰�?*/

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();    /*杩欓噷闅忛煶棰戜細鏈変笉鍚�*/
#endif
}

/*绋�??�?閲嶆柊鍚�鍔�锛屾仮澶嶉煶棰�?*/

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();   /*杩欓噷闅忛煶棰戜細鏈変笉鍚�*/
#endif
}
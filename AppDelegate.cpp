#include "AppDelegate.h"
#include "LogoSplashScene.h"

#ifdef SDKBOX_ENABLED
#include "PluginIAP/PluginIAP.h"
#endif
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

#define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 540);
//static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 540);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2560, 1440);

Size visibleSize;

int currentLevel = 1;
int score = 0;
int lives = 2;
int levelDoneCount = 0;
int itemCounter = 0;
int badItemCounter = 0;
int highScore = 0;
int mainTheme;
int inGameMusic = -2;
int showAdsCounter = 0;

bool isSoundsEnable = true;
bool isMusicEnable = true;
bool isAdsEnable = true;

float itemSpeed = 0;
float itemSpawnFreq = 1.8f;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    experimental::AudioEngine::end();
    Director::getInstance()->release();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
#ifdef SDKBOX_ENABLED
    sdkbox::IAP::init();
#endif
#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::init();
#endif
    // initialize director
    Director::getInstance()->retain();
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("health_store", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("health_store");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
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

    UserDefault* def = UserDefault::getInstance();

    isSoundsEnable = def->getBoolForKey("IS_SOUNDS_ENABLE", true);
    isMusicEnable = def->getBoolForKey("IS_MUSIC_ENABLE", true);
    isAdsEnable = def->getBoolForKey("IS_ADS_ENABLE", true);

    //Load Sprite Sheets
    auto spritecache = SpriteFrameCache::getInstance();

    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_1.plist");
    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_2.plist");
    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_3.plist");
    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_4.plist");
    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_5.plist");
    spritecache->addSpriteFramesWithFile("hdr/hs_spritesheet_6.plist");

#ifdef SDKBOX_ENABLED
    if (isAdsEnable)
    {
        sdkbox::PluginAdMob::cache("next_level");
        sdkbox::PluginAdMob::cache("rewarded");
    }
#endif

    visibleSize = Director::getInstance()->getVisibleSize();
  
    // create a scene. it's an autorelease object

    auto LogoSplashScene = LogoSplashScene::createScene();
    // run
    director->runWithScene(LogoSplashScene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

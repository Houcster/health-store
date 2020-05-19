#include "MainMenuScene.h"
#include "LogoSplashScene.h"
#include "AppDelegate.h"

USING_NS_CC;

extern Size visibleSize;

Scene* LogoSplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LogoSplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LogoSplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin(); 

    auto layerGradient = LayerGradient::create(Color4B(110, 190, 235, 255), Color4B(255, 255, 255, 255), Point(1, 1));
    layerGradient->setPosition(origin);
    addChild(layerGradient);

    if (SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hs_spritesheet.plist"))
    {
        CCLOG("GG");
        auto logoSprite = Sprite::createWithSpriteFrameName("logo");
        logoSprite->setContentSize(Size(visibleSize.width * 0.3, visibleSize.height * 0.535));
        logoSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
        logoSprite->setOpacity(0);
        addChild(logoSprite);

        auto fadeIn = FadeIn::create(3.0f);
        logoSprite->runAction(fadeIn);
        scheduleOnce(CC_SCHEDULE_SELECTOR(LogoSplashScene::showMainMenu), 3.0f);
    }
    else
    {
        auto label = Label::createWithTTF("Looks like we have problems\n with files loading\n\n Please, try again\n or reinstall game", "fonts/arial.ttf", 44);      
        label->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
        label->setColor(Color3B::BLACK);
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        this->addChild(label, 1);
    }
  
    return true;
}

void LogoSplashScene::showMainMenu(float dt)
{
    auto MainMenuScene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene));
}

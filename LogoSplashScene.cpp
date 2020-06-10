#include "MainMenuScene.h"
#include "LogoSplashScene.h"
#include "AppDelegate.h"
#include "AudioEngine.h"

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
    if (!Layer::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin(); 

    auto layerGradient = LayerGradient::create(Color4B(110, 190, 235, 255), Color4B(255, 255, 255, 255), Point(1, 1));
    layerGradient->setPosition(origin);
    addChild(layerGradient);

    if (   SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_1.plist")
        && SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_2.plist")
        && SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_3.plist")
        && SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_4.plist")
        && SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_5.plist")
        && SpriteFrameCache::getInstance()->isSpriteFramesWithFileLoaded("hdr/hs_spritesheet_6.plist"))
    {
        CCLOG("GG");
        auto logoSprite = Sprite::createWithSpriteFrameName("logo");
        logoSprite->setContentSize(Size(visibleSize.width * 0.3, visibleSize.height * 0.535));
        logoSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
        logoSprite->setOpacity(0);
        addChild(logoSprite);

        auto fadeIn = FadeIn::create(2.5f);
        logoSprite->runAction(fadeIn);

        experimental::AudioEngine::preload("audio/main_theme.mp3");
        experimental::AudioEngine::preload("audio/mainMusic_1.mp3");
        experimental::AudioEngine::preload("audio/mainMusic_2.mp3");
        experimental::AudioEngine::preload("audio/buttonSound.mp3");
        experimental::AudioEngine::preload("audio/basketSound.mp3");
        experimental::AudioEngine::preload("audio/loseSound.mp3");
        experimental::AudioEngine::preload("audio/winSound.mp3");
        experimental::AudioEngine::preload("audio/trashSound.mp3");

        scheduleOnce(CC_SCHEDULE_SELECTOR(LogoSplashScene::showMainMenu), 2.5f);
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

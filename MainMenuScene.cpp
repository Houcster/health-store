#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "GamingScene.h"
#include "LevelCompleteScene.h"
#include "AudioEngine.h"
#include "SettingsScene.h"
#include "RulesScene.h"
#include "InfoScene.h"

USING_NS_CC;
extern Size visibleSize;
extern int highScore;
extern int inGameMusic;
extern int mainTheme;
extern bool isSoundsEnable;
extern bool isMusicEnable;

static int bgMusic = -1;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    UserDefault* def = UserDefault::getInstance();

    highScore = def->getIntegerForKey("HIGHSCORE", 0);

    visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto glview = Director::getInstance()->getOpenGLView();

    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/main_theme.mp3");
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/main_theme.mp3", true);

    auto mainMenuBGSprite = Sprite::createWithSpriteFrameName("mainMenuBG");
    mainMenuBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    mainMenuBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(mainMenuBGSprite);

    auto label = Label::createWithTTF("High score: " + std::to_string(highScore), "fonts/arial.ttf", 40);
    label->setPosition(visibleSize.width * 0.75f, visibleSize.height * 0.85f);
    label->setColor(Color3B::BLACK);
    addChild(label, 1);

    auto playItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("playButton"),
        Sprite::createWithSpriteFrameName("playButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::createGamingScene, this));

    playItem->setPosition(visibleSize.width * 0.265f, visibleSize.height * 0.48f);
    playItem->setContentSize(Size(visibleSize.width * 0.315f, visibleSize.height * 0.19f));
    playItem->getNormalImage()->setContentSize(playItem->getContentSize());
    playItem->getSelectedImage()->setContentSize(playItem->getContentSize());

    auto closeItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("closeButton"),
        Sprite::createWithSpriteFrameName("closeButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    closeItem->setPosition(visibleSize.width * 0.935f, visibleSize.height * 0.12f);
    closeItem->setContentSize(Size(visibleSize.width * 0.0675f, visibleSize.height * 0.12f));
    closeItem->getNormalImage()->setContentSize(closeItem->getContentSize());
    closeItem->getSelectedImage()->setContentSize(closeItem->getContentSize());

    //closeItem->setScale(screenSize.width * 0.000225f);

    auto settingsItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("settingsButton"),
        Sprite::createWithSpriteFrameName("settingsButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::showSettingsScene, this));

    settingsItem->setPosition(visibleSize.width * 0.15f, visibleSize.height * 0.22f);
    settingsItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
    settingsItem->getNormalImage()->setContentSize(settingsItem->getContentSize());
    settingsItem->getSelectedImage()->setContentSize(settingsItem->getContentSize());

    auto rulesItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("rulesButton"),
        Sprite::createWithSpriteFrameName("rulesButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::showRulesScene, this));

    rulesItem->setPosition(visibleSize.width * 0.265f, visibleSize.height * 0.22f);
    rulesItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
    rulesItem->getNormalImage()->setContentSize(rulesItem->getContentSize());
    rulesItem->getSelectedImage()->setContentSize(rulesItem->getContentSize());

    auto infoItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("infoButton"),
        Sprite::createWithSpriteFrameName("infoButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::showInfoScene, this));

    infoItem->setPosition(visibleSize.width * 0.38f, visibleSize.height * 0.22f);
    infoItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
    infoItem->getNormalImage()->setContentSize(infoItem->getContentSize());
    infoItem->getSelectedImage()->setContentSize(infoItem->getContentSize());

    auto* menu = Menu::create(playItem,
                              closeItem,
                              settingsItem,
                              rulesItem,
                              infoItem,
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    experimental::AudioEngine::stop(inGameMusic);

    if (experimental::AudioEngine::getState(mainTheme) != experimental::AudioEngine::AudioState::PLAYING && isMusicEnable)
    {
        mainTheme = experimental::AudioEngine::play2d("audio/main_theme.mp3", true, 0.4f);
    }

    return true;
}

void MainMenuScene::showSettingsScene(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }
    
    auto SettingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, SettingsScene));
}

void MainMenuScene::showRulesScene(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    auto RulesScene = RulesScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, RulesScene));
}

void MainMenuScene::showInfoScene(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    auto InfoScene = InfoScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, InfoScene));
}

void MainMenuScene::createGamingScene(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }
    experimental::AudioEngine::stop(mainTheme);
    //experimental::AudioEngine::play2d("audio/buttonSound.mp3");

    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GamingScene));

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{   
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

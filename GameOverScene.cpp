#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "AudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// include JniHelper.h
#include "platform\android\jni\JniHelper.h"
#endif

USING_NS_CC;

extern int score;
extern int highScore;
extern int lives;
extern int currentLevel;
extern Size visibleSize;
extern int levelDoneCount;
extern int itemCounter;
extern int badItemCounter;
extern float itemSpeed;
extern bool isSoundsEnable;
extern bool isMusicEnable;
extern bool isAdsEnable;
extern float itemSpawnFreq;

static bool isRewarded = false;
MenuItemSprite* restartItem;

Scene* GameOverScene::createScene()
{
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameOverBGSprite = Sprite::createWithSpriteFrameName("gameOverBG");
    gameOverBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    gameOverBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(gameOverBGSprite);

    if (score > highScore)
    {
        UserDefault* def = UserDefault::getInstance();
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
        def->flush();
    }

    gos_label = Label::createWithTTF("Game Over!\nScore: " + std::to_string(score), "fonts/arial.ttf", 44);
    if (gos_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        gos_label->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.8f);
        gos_label->setColor(Color3B::BLACK);
        gos_label->setHorizontalAlignment(TextHAlignment::CENTER);
        // add the label as a child to this layer
        this->addChild(gos_label, 1);
    }


    restartItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("continueNoAds"),
        Sprite::createWithSpriteFrameName("continueNoAdsPressed"));

    restartItem->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.56f);
    restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (isAdsEnable)
    { 
        if (lives == 1 && sdkbox::PluginAdMob::isAvailable("rewarded"))
        {
            restartItem->setCallback(CC_CALLBACK_1(GameOverScene::continueGame, this));
            restartItem->setNormalImage(Sprite::createWithSpriteFrameName("continueByAds"));
            restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("continueByAdsPressed"));
            restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
            restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
            restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
        }
        else
        {
            restartItem->setCallback(CC_CALLBACK_1(GameOverScene::restartGame, this));
            restartItem->setNormalImage(Sprite::createWithSpriteFrameName("gmovrRestartButton"));
            restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("gmovrRestartButtonPressed"));
            restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
            restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
            restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
        }
    }
    else
    {
        if (lives == 1)
        {
            restartItem->setCallback(CC_CALLBACK_1(GameOverScene::continueGame, this));
            restartItem->setNormalImage(Sprite::createWithSpriteFrameName("continueNoAds"));
            restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("continueNoAdsPressed"));
            restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
            restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
            restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
        }
        else
        {
            restartItem->setCallback(CC_CALLBACK_1(GameOverScene::restartGame, this));
            restartItem->setNormalImage(Sprite::createWithSpriteFrameName("gmovrRestartButton"));
            restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("gmovrRestartButtonPressed"));
            restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
            restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
            restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
        }
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    if (lives == 1)
    {
        restartItem->setCallback(CC_CALLBACK_1(GameOverScene::continueGame, this));
        restartItem->setNormalImage(Sprite::createWithSpriteFrameName("continueNoAds"));
        restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("continueNoAdsPressed"));
        restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
        restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
        restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
    }
    else
    {
        restartItem->setCallback(CC_CALLBACK_1(GameOverScene::restartGame, this));
        restartItem->setNormalImage(Sprite::createWithSpriteFrameName("gmovrRestartButton"));
        restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("gmovrRestartButtonPressed"));
        restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
        restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
        restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
    }
    
#endif


    auto shareItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("gmovrShareButton"),
        Sprite::createWithSpriteFrameName("gmovrShareButtonPressed"),
        CC_CALLBACK_1(GameOverScene::shareResults, this));

    shareItem->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.38f);
    shareItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
    shareItem->getNormalImage()->setContentSize(shareItem->getContentSize());
    shareItem->getSelectedImage()->setContentSize(shareItem->getContentSize());

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("gmovrMenuButton"),
        Sprite::createWithSpriteFrameName("gmovrMenuButtonPressed"),
        CC_CALLBACK_1(GameOverScene::showMainMenu, this));

    mainMenuItem->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.20f);
    mainMenuItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
    mainMenuItem->getNormalImage()->setContentSize(mainMenuItem->getContentSize());
    mainMenuItem->getSelectedImage()->setContentSize(mainMenuItem->getContentSize());

    auto* menu = Menu::create(restartItem, 
                              shareItem, 
                              mainMenuItem,
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::setListener(this);
#endif
    return true;
}

void GameOverScene::restartGame(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    lives = 2;
    currentLevel = 1;
    score = 0;
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (isRewarded)
    {
        auto GamingScene = GamingScene::createScene();
        Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
        isRewarded = false;
    }
    else
    {
        lives = 2;
        currentLevel = 1;
        score = 0;
        auto GamingScene = GamingScene::createScene();
        Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
        isRewarded = false;
    }
#endif

}

void GameOverScene::continueGame(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (isAdsEnable)
    {
            experimental::AudioEngine::stopAll();
            sdkbox::PluginAdMob::show("rewarded");

            restartItem->setCallback(CC_CALLBACK_1(GameOverScene::restartGame, this));
            restartItem->setNormalImage(Sprite::createWithSpriteFrameName("gmovrRestartButton"));
            restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("gmovrRestartButtonPressed"));
            restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
            restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
            restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
    }
    else
    {
        auto GamingScene = GamingScene::createScene();
        Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
    }
#endif
}

void GameOverScene::continueGameByAds(cocos2d::Ref* pSender)
{
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, GamingScene));
}

void GameOverScene::getReward()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    restartItem->setCallback(CC_CALLBACK_1(GameOverScene::continueGameByAds, this));
    restartItem->setNormalImage(Sprite::createWithSpriteFrameName("readyButton"));
    restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("readyButtonPressed"));
    restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
    restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
    restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
#endif
}

void GameOverScene::shareResults(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    JniMethodInfo socialShare;

    if (JniHelper::getStaticMethodInfo(socialShare, "org/cocos2dx/cpp/AppActivity", "socialShare", "(I)V"))
    {
        socialShare.env->CallStaticVoidMethod(socialShare.classID, socialShare.methodID, score);
    }
    #endif

}

void GameOverScene::showMainMenu(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    currentLevel = 1;
    score = 0;
    lives = 2;
    levelDoneCount = 0;
    itemCounter = 0;
    badItemCounter = 0;
    itemSpeed = 0;
    itemSpawnFreq = 1.8f;
    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, MainMenuScene));
}

#ifdef SDKBOX_ENABLED
void GameOverScene::adViewDidReceiveAd(const std::string &name) {}
void GameOverScene::adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {}
void GameOverScene::adViewWillPresentScreen(const std::string &name) {}
void GameOverScene::adViewDidDismissScreen(const std::string &name) {}
void GameOverScene::adViewWillDismissScreen(const std::string &name) {}
void GameOverScene::adViewWillLeaveApplication(const std::string &name) {}
void GameOverScene::reward(const std::string &name, const std::string &currency, double amount)
{
    isRewarded = true;
    restartItem->setNormalImage(Sprite::createWithSpriteFrameName("readyButton"));
    restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("readyButtonPressed"));
    restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
    restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
    restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
}
#endif



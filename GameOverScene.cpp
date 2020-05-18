#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

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

    gos_label = Label::createWithTTF("Game Over!\nScore was: " + std::to_string(score), "fonts/arial.ttf", 44);
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


    auto restartItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("keepGoNoAds"),
        Sprite::createWithSpriteFrameName("keepGoNoAdsPressed"),
        CC_CALLBACK_1(GameOverScene::createGamingScene, this));

    restartItem->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.56f);
    restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));

    if (lives == 1)
    {
        restartItem->setNormalImage(Sprite::createWithSpriteFrameName("keepGoNoAds"));
        restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("keepGoNoAdsPressed"));
        restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
        restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
        restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
    }
    else if (lives == 0)
    {
        restartItem->setNormalImage(Sprite::createWithSpriteFrameName("gmovrRestartButton"));
        restartItem->setSelectedImage(Sprite::createWithSpriteFrameName("gmovrRestartButtonPressed"));
        restartItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1325f));
        restartItem->getNormalImage()->setContentSize(restartItem->getContentSize());
        restartItem->getSelectedImage()->setContentSize(restartItem->getContentSize());
    }




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

    return true;
}

void GameOverScene::createGamingScene(Ref* pSender)
{
    //Метод создаёт игровую сцену(Gaming Scene), при этом текущая сцена(MainMenuScene) удаляется
    if (lives != 0)
    {
        auto GamingScene = GamingScene::createScene();
        Director::getInstance()->replaceScene(GamingScene);
    }
    else
    {
        lives = 2;
        currentLevel = 1;
        score = 0;
        auto GamingScene = GamingScene::createScene();
        Director::getInstance()->replaceScene(GamingScene);
    }
}

void GameOverScene::shareResults(cocos2d::Ref* pSender)
{

}

void GameOverScene::showMainMenu(cocos2d::Ref* pSender)
{
    currentLevel = 1;
    score = 0;
    lives = 2;
    levelDoneCount = 0;
    itemCounter = 0;
    badItemCounter = 0;
    itemSpeed = 0;
    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, MainMenuScene));
}



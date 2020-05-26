#include "MainMenuScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "LevelCompleteScene.h"
#include "AudioEngine.h"

USING_NS_CC;

extern int score;
extern int highScore;
extern int currentLevel;
extern int levelDoneCount;
extern Size visibleSize;
extern int itemCounter;
extern float itemSpeed;
extern int lives;
extern int badItemCounter;
extern bool isSoundsEnable;
extern bool isMusicEnable;


Scene* LevelCompleteScene::createScene()
{
    return LevelCompleteScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelCompleteScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();\

    auto completeLevelBGSprite = Sprite::createWithSpriteFrameName("completeLevelBG");
    completeLevelBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    completeLevelBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(completeLevelBGSprite);

    lcs_label = Label::createWithTTF("You complete level: " + std::to_string(currentLevel), "fonts/arial.ttf", 44);
    if (lcs_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        lcs_label->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.75f);
        lcs_label->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(lcs_label, 1);
    }

    if (score > highScore)
    {
        UserDefault* def = UserDefault::getInstance();
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
        def->flush();
    }

    auto nextItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("cmplvlNiceButton"),
        Sprite::createWithSpriteFrameName("cmplvlNiceButtonPressed"),
        CC_CALLBACK_1(LevelCompleteScene::createGamingScene, this));

    nextItem->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.52f);
    nextItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1585f));
    nextItem->getNormalImage()->setContentSize(nextItem->getContentSize());
    nextItem->getSelectedImage()->setContentSize(nextItem->getContentSize());

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("cmplvlMenuButton"),
        Sprite::createWithSpriteFrameName("cmplvlMenuButtonPressed"),
        CC_CALLBACK_1(LevelCompleteScene::showMainMenu, this));

    mainMenuItem->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.32f);
    mainMenuItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.1585f));
    mainMenuItem->getNormalImage()->setContentSize(mainMenuItem->getContentSize());
    mainMenuItem->getSelectedImage()->setContentSize(mainMenuItem->getContentSize());

    auto* menu = Menu::create(nextItem,
                              mainMenuItem,      
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void LevelCompleteScene::createGamingScene(Ref* pSender)
{
    //Метод создаёт игровую сцену(Gaming Scene), при этом текущая сцена(MainMenuScene) удаляется
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    currentLevel++;
    if (currentLevel > 11)
    {
        levelDoneCount += 50;
    }
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GamingScene));
}

void LevelCompleteScene::showMainMenu(Ref* pSender)
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
    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1, MainMenuScene));

}

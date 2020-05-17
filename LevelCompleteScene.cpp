#include "MainMenuScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "LevelCompleteScene.h"

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

    LayerColor* _bgColor = LayerColor::create(Color4B(157, 187, 227, 255));
    this->addChild(_bgColor, -10);

    Vec2 origin = Director::getInstance()->getVisibleOrigin();\

    auto completeLevelBGSprite = Sprite::createWithSpriteFrameName("completeLevelBG");
    completeLevelBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    completeLevelBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(completeLevelBGSprite);

    gos_label = Label::createWithTTF("You complete level: " + std::to_string(currentLevel), "fonts/arial.ttf", 44);
    if (gos_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        gos_label->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.75f);
        gos_label->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(gos_label, 1);
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
        CC_CALLBACK_1(LevelCompleteScene::createMainMenuScene, this));

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

    currentLevel++;
    if (currentLevel > 4)
    {
        levelDoneCount += 20;
    }
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GamingScene));
}

void LevelCompleteScene::createMainMenuScene(Ref* pSender)
{
    currentLevel = 1;
    score = 0;
    lives = 3;
    levelDoneCount = 0;
    itemCounter = 0;
    badItemCounter = 0;
    highScore = 0;
    itemSpeed = 0;
    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, MainMenuScene));

}

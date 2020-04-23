#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "LevelCompleteScene.h"

USING_NS_CC;

extern int score;
extern int currentLevel;
extern int levelDoneCount;
extern Size visibleSize;
extern int itemCounter;
extern float itemSpeed;

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    gos_label = Label::createWithTTF("You complete level: " + std::to_string(currentLevel), "fonts/Marker Felt.ttf", 44);
    if (gos_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        gos_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 1.4f));

        // add the label as a child to this layer
        this->addChild(gos_label, 1);
    }

    auto menu_item_1 = MenuItemFont::create("Continue",
        CC_CALLBACK_1(LevelCompleteScene::createGamingScene, this));
    auto menu_item_2 = MenuItemFont::create("Exit",
        CC_CALLBACK_1(LevelCompleteScene::menuCloseCallback, this));

    menu_item_1->setPosition(Size(480.0f, 250.0f));
    menu_item_2->setPosition(Size(480.0f, 150.0f));

    auto* menu = Menu::create(menu_item_1,
        menu_item_2,
        NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void LevelCompleteScene::createGamingScene(Ref* pSender)
{
    //Метод создаёт игровую сцену(Gaming Scene), при этом текущая сцена(MainMenuScene) удаляется
    currentLevel++;
    if (currentLevel > 3)
    {
        levelDoneCount += 20;
    }
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GamingScene));
}

void LevelCompleteScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}



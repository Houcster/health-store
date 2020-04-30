#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GamingScene.h"
#include "LevelCompleteScene.h"

USING_NS_CC;
extern Size visibleSize;
extern int highScore;

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
    if ( !Scene::init() )
    {
        return false;
    }

    LayerColor* _bgColor = LayerColor::create(Color4B(124, 130, 130, 255));
    this->addChild(_bgColor, -10);

    visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto glview = Director::getInstance()->getOpenGLView();
    auto screenSize = glview->getFrameSize();

    auto mainMenuBGSprite = Sprite::createWithSpriteFrameName("mainMenuBG");
    mainMenuBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    mainMenuBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(mainMenuBGSprite);

    auto label = Label::createWithTTF("High score: " + std::to_string(highScore), "fonts/Marker Felt.ttf", 34);
    label->setPosition(visibleSize.width * 0.8f, visibleSize.height * 0.9f);
    label->setColor(Color3B::GREEN);
    addChild(label, 1);

    auto playItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("playButton"),
        Sprite::createWithSpriteFrameName("playButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::menuPlayCallback, this));

    playItem->setPosition(visibleSize.width * 0.295f, visibleSize.height * 0.58f);     
    //playItem->setScale(visibleSize.width * 0.000225f);
    playItem->setScale(screenSize.width* 0.000225f);

    auto closeItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("closeButton"),
        Sprite::createWithSpriteFrameName("closeButtonPressed"),
        CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    closeItem->setPosition(visibleSize.width * 0.85f, visibleSize.height * 0.12f);
    closeItem->setScale(screenSize.width * 0.000225f);

    auto soundItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("soundButton"),
        Sprite::createWithSpriteFrameName("soundButtonPressed"),
        NULL);

    soundItem->setPosition(visibleSize.width * 0.125f, visibleSize.height * 0.22f);
    soundItem->setScale(screenSize.width * 0.000225f);

    auto rulesItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("rulesButton"),
        Sprite::createWithSpriteFrameName("rulesButtonPressed"),
        NULL);

    rulesItem->setPosition(visibleSize.width * 0.295f, visibleSize.height * 0.22f);
    rulesItem->setScale(screenSize.width * 0.000225f);

    auto infoItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("infoButton"),
        Sprite::createWithSpriteFrameName("infoButtonPressed"),
        NULL);

    infoItem->setPosition(visibleSize.width * 0.465f, visibleSize.height * 0.22f);
    infoItem->setScale(screenSize.width * 0.000225f);

    auto* menu = Menu::create(playItem, 
                              closeItem,
                              soundItem,
                              rulesItem,
                              infoItem,
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void MainMenuScene::createGamingScene(Ref* pSender)
{
    //����� ������ ������� �����(Gaming Scene), ��� ���� ������� �����(MainMenuScene) ���������
    auto GamingScene = GamingScene::createScene();  
    Director::getInstance()->pushScene(GamingScene);  
    //auto SubLevelScene = LevelCompleteScene::createScene();
    //Director::getInstance()->pushScene(SubLevelScene);
}

void MainMenuScene::menuPlayCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GamingScene));

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

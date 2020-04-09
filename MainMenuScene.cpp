#include "MainMenuScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    auto menu_item_1 = MenuItemFont::create("Play", 
                                            CC_CALLBACK_1(MainMenuScene::createGamingScene, this));
    auto menu_item_2 = MenuItemFont::create("Exit", 
                                            CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));

    menu_item_1->setPosition(visibleSize.width / 2, 
                             (visibleSize.height / 3) * 2);
    menu_item_2->setPosition(visibleSize.width / 2, 
                             (visibleSize.height / 3) * 1);

    auto* menu = Menu::create(menu_item_1, 
                              menu_item_2, 
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void MainMenuScene::createGamingScene(Ref* pSender)
{
    //Метод создаёт игровую сцену(Gaming Scene), при этом текущая сцена(MainMenuScene) удаляется
    auto GamingScene = GamingScene::createScene();
    Director::getInstance()->pushScene(GamingScene);    
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

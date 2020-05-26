#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "RulesScene.h"

USING_NS_CC;

extern Size visibleSize;
extern bool isSoundsEnable;

Scene* RulesScene::createScene()
{
    return RulesScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RulesScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rulesBGSprite = Sprite::createWithSpriteFrameName("rulesBG");
    rulesBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    rulesBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(rulesBGSprite);

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("backButton"),
        Sprite::createWithSpriteFrameName("backButtonPressed"),
        CC_CALLBACK_1(RulesScene::showMainMenu, this));

    mainMenuItem->setPosition(visibleSize.width * 0.04f, visibleSize.height * 0.065f);
    mainMenuItem->setContentSize(Size(visibleSize.width * 0.055f, visibleSize.height * 0.095f));
    mainMenuItem->getNormalImage()->setContentSize(mainMenuItem->getContentSize());
    mainMenuItem->getSelectedImage()->setContentSize(mainMenuItem->getContentSize());

    auto* menu = Menu::create(mainMenuItem,
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void RulesScene::showMainMenu(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, MainMenuScene));
}
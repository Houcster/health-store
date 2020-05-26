#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "InfoScene.h"

USING_NS_CC;

extern Size visibleSize;
extern bool isSoundsEnable;

Scene* InfoScene::createScene()
{
    return InfoScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool InfoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = cocos2d::LayerColor::create(Color4B(175, 200, 115, 255)); //Color4B(175, 200, 115, 255)Color4B(250, 190, 25, 255)
    this->addChild(bg);

    auto developerLabel_1 = Label::createWithTTF("Main programmer, Producer, etc.: \nAnton 'Houcster' Guryev", "fonts/arial.ttf", 44);
    developerLabel_1->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.875f);
    developerLabel_1->setColor(Color3B::BLACK);
    developerLabel_1->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(developerLabel_1);

    auto developerLabel_2 = Label::createWithTTF("Graphic designer: \nNinaWave", "fonts/arial.ttf", 44);
    developerLabel_2->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.625f);
    developerLabel_2->setColor(Color3B::BLACK);
    developerLabel_2->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(developerLabel_2);

    auto developerLabel_3 = Label::createWithTTF("Sounddesing: \nmic. (Natry)", "fonts/arial.ttf", 44);
    developerLabel_3->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.375f);
    developerLabel_3->setColor(Color3B::BLACK);
    developerLabel_3->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(developerLabel_3);

    auto contactsLabel_3 = Label::createWithTTF("Developed with Cocos2d-x.\nContacts us at itszhukgaming@gmail.com", "fonts/arial.ttf", 34);
    contactsLabel_3->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.1f);
    contactsLabel_3->setColor(Color3B::BLACK);
    contactsLabel_3->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(contactsLabel_3);

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("backButton"),
        Sprite::createWithSpriteFrameName("backButtonPressed"),
        CC_CALLBACK_1(InfoScene::showMainMenu, this));

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

void InfoScene::showMainMenu(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, MainMenuScene));
}
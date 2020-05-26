#include "MainMenuScene.h"
#include "GamingScene.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "LevelCompleteScene.h"
#include "AudioEngine.h"
#include "SettingsScene.h"

USING_NS_CC;


extern Size visibleSize;
extern bool isSoundsEnable;
extern bool isMusicEnable;

MenuItemSprite* soundStateItem;
MenuItemSprite* musicStateItem;


Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin(); 

    auto bg = cocos2d::LayerColor::create(Color4B(110, 190, 235, 255)); //Color4B(175, 200, 115, 255)Color4B(250, 190, 25, 255)
    this->addChild(bg);


    sc_soundLabel = Label::createWithTTF("Sound", "fonts/arial.ttf", 44);
    if (sc_soundLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        sc_soundLabel->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.75f);
        sc_soundLabel->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(sc_soundLabel, 1);
    }

    sc_musicLabel = Label::createWithTTF("Music", "fonts/arial.ttf", 44);
    if (sc_musicLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        sc_musicLabel->setPosition(visibleSize.width * 0.4f, visibleSize.height * 0.45f);
        sc_musicLabel->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(sc_musicLabel, 1);
    }

    soundStateItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("enableIcon"),
        Sprite::createWithSpriteFrameName("enableIcon"),
        CC_CALLBACK_1(SettingsScene::setSoundsEnabling, this)); 

    soundStateItem->setPosition(visibleSize.width * 0.6f, visibleSize.height * 0.75f);
    soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
    
    if (isSoundsEnable)
    {
        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());
    }
    else
    {
        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());
    }

    musicStateItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("enableIcon"),
        Sprite::createWithSpriteFrameName("enableIcon"),
        CC_CALLBACK_1(SettingsScene::setMusicEnabling, this));

    musicStateItem->setPosition(visibleSize.width * 0.6f, visibleSize.height * 0.45f);
    musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));

    if (isMusicEnable)
    {
        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());
    }
    else
    {
        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());
    }

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("backButton"),
        Sprite::createWithSpriteFrameName("backButtonPressed"),
        CC_CALLBACK_1(SettingsScene::showMainMenu, this));

    mainMenuItem->setPosition(visibleSize.width * 0.04f, visibleSize.height * 0.065f);
    mainMenuItem->setContentSize(Size(visibleSize.width * 0.055f, visibleSize.height * 0.095f));
    mainMenuItem->getNormalImage()->setContentSize(mainMenuItem->getContentSize());
    mainMenuItem->getSelectedImage()->setContentSize(mainMenuItem->getContentSize());

    auto* menu = Menu::create(soundStateItem,
                              musicStateItem,
                              mainMenuItem,
                              NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

void SettingsScene::setSoundsEnabling(Ref* pSender)
{
    
    UserDefault* def = UserDefault::getInstance();

    if (isSoundsEnable)
    {
        isSoundsEnable = false;
        isMusicEnable = false;
        def->setBoolForKey("IS_SOUNDS_ENABLE", isSoundsEnable);
        def->setBoolForKey("IS_MUSIC_ENABLE", isMusicEnable);

        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());

        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());

        experimental::AudioEngine::stopAll();
    }
    else
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");

        isSoundsEnable = true;
        isMusicEnable = true;
        def->setBoolForKey("IS_SOUNDS_ENABLE", isSoundsEnable);
        def->setBoolForKey("IS_MUSIC_ENABLE", isMusicEnable);

        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());

        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());
    }

    
    def->flush();
}

void SettingsScene::setMusicEnabling(Ref* pSender)
{
    UserDefault* def = UserDefault::getInstance();

    if (isMusicEnable)
    {
        isMusicEnable = false;
        def->setBoolForKey("IS_MUSIC_ENABLE", isMusicEnable);

        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());

        experimental::AudioEngine::stopAll();
    }
    else if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");

        isMusicEnable = true;
        def->setBoolForKey("IS_MUSIC_ENABLE", isMusicEnable);

        musicStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        musicStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        musicStateItem->getNormalImage()->setContentSize(musicStateItem->getContentSize());
        musicStateItem->getSelectedImage()->setContentSize(musicStateItem->getContentSize());
    }


    def->flush();
}

void SettingsScene::showMainMenu(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

    auto MainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionSlideInL::create(1, MainMenuScene));
}
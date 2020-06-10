#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "SettingsScene.h"

USING_NS_CC;

extern Size visibleSize;
extern bool isSoundsEnable;
extern bool isMusicEnable;
extern bool isAdsEnable;

MenuItemSprite* soundStateItem;
MenuItemSprite* musicStateItem;
MenuItemSprite* removeAdsItem;
Label* removeAdsLabel;

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

    auto settingsBGSprite = Sprite::createWithSpriteFrameName("settingsBG");
    settingsBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    settingsBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(settingsBGSprite);

    auto soundLabel = Label::createWithTTF("Sound", "fonts/arial.ttf", 44);
    soundLabel->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.65f);
    soundLabel->setColor(Color3B::BLACK);
    this->addChild(soundLabel, 1);

    auto musicLabel = Label::createWithTTF("Music", "fonts/arial.ttf", 44);
    musicLabel->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.35f);
    musicLabel->setColor(Color3B::BLACK);
    this->addChild(musicLabel, 1);

    removeAdsLabel = Label::createWithTTF("Ads is available", "fonts/arial.ttf", 44);
    removeAdsLabel->setPosition(visibleSize.width * 0.7f, visibleSize.height * 0.85f);
    removeAdsLabel->setColor(Color3B::BLACK);
    if (isAdsEnable)
    {
        removeAdsLabel->setString("Ads are available");
    }
    else
    {
        removeAdsLabel->setString("Ads removed");
    }

    this->addChild(removeAdsLabel, 1);

    soundStateItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("enableIcon"),
        Sprite::createWithSpriteFrameName("enableIcon"),
        CC_CALLBACK_1(SettingsScene::setSoundsEnabling, this)); 

    soundStateItem->setPosition(visibleSize.width * 0.3f, visibleSize.height * 0.65f);
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

    musicStateItem->setPosition(visibleSize.width * 0.3f, visibleSize.height * 0.35f);
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

    removeAdsItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("removeAdsButton"),
        Sprite::createWithSpriteFrameName("removeAdsButtonPressed"),
        Sprite::createWithSpriteFrameName("removeUnenable"),
        CC_CALLBACK_1(SettingsScene::removeAds, this));

    removeAdsItem->setPosition(visibleSize.width * 0.7f, visibleSize.height * 0.65f);
    removeAdsItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.15f));
    removeAdsItem->getNormalImage()->setContentSize(removeAdsItem->getContentSize());
    removeAdsItem->getSelectedImage()->setContentSize(removeAdsItem->getContentSize());
    removeAdsItem->getDisabledImage()->setContentSize(removeAdsItem->getContentSize());

    if (!isAdsEnable)
    {
        removeAdsItem->setEnabled(false);
    }

    auto restoreAdsItem = MenuItemSprite::create(
            Sprite::createWithSpriteFrameName("restoreAdsButton"),
            Sprite::createWithSpriteFrameName("restoreAdsButtonPressed"),
            CC_CALLBACK_1(SettingsScene::restoreAds, this));

    restoreAdsItem->setPosition(visibleSize.width * 0.7f, visibleSize.height * 0.35f);
    restoreAdsItem->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.15f));
    restoreAdsItem->getNormalImage()->setContentSize(removeAdsItem->getContentSize());
    restoreAdsItem->getSelectedImage()->setContentSize(removeAdsItem->getContentSize());

    auto mainMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("backButton"),
        Sprite::createWithSpriteFrameName("backButtonPressed"),
        CC_CALLBACK_1(SettingsScene::showMainMenu, this));

    mainMenuItem->setPosition(visibleSize.width * 0.04f, visibleSize.height * 0.0715f);
    mainMenuItem->setContentSize(Size(visibleSize.width * 0.075f, visibleSize.height * 0.1325f));
    mainMenuItem->getNormalImage()->setContentSize(mainMenuItem->getContentSize());
    mainMenuItem->getSelectedImage()->setContentSize(mainMenuItem->getContentSize());

    auto* menu = Menu::create(
        soundStateItem,
        musicStateItem,
        removeAdsItem,
        restoreAdsItem,
        mainMenuItem,
        NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

#ifdef SDKBOX_ENABLED
    sdkbox::IAP::refresh();
    sdkbox::IAP::setListener(this);
#endif

    return true;
}

void SettingsScene::setSoundsEnabling(Ref* pSender)
{  
    UserDefault* def = UserDefault::getInstance();

    if (isSoundsEnable)
    {
        isSoundsEnable = false;
        def->setBoolForKey("IS_SOUNDS_ENABLE", isSoundsEnable);

        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("unEnableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());
    }
    else
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");

        isSoundsEnable = true;
        def->setBoolForKey("IS_SOUNDS_ENABLE", isSoundsEnable);

        soundStateItem->setNormalImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setSelectedImage(Sprite::createWithSpriteFrameName("enableIcon"));
        soundStateItem->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.15f));
        soundStateItem->getNormalImage()->setContentSize(soundStateItem->getContentSize());
        soundStateItem->getSelectedImage()->setContentSize(soundStateItem->getContentSize());
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
    else
    {
        if (isSoundsEnable)
        {
            experimental::AudioEngine::play2d("audio/buttonSound.mp3");
        }

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

void SettingsScene::removeAds(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

#ifdef SDKBOX_ENABLED
    sdkbox::IAP::purchase("remove_ads");
#endif
}

void SettingsScene::restoreAds(cocos2d::Ref* pSender)
{
    if (isSoundsEnable)
    {
        experimental::AudioEngine::play2d("audio/buttonSound.mp3");
    }

#ifdef SDKBOX_ENABLED
    sdkbox::IAP::restore();
#endif
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

#ifdef SDKBOX_ENABLED
void SettingsScene::onInitialized(bool ok){}
void SettingsScene::onSuccess(sdkbox::Product const& p)
{
    UserDefault* def = UserDefault::getInstance();
    isAdsEnable = false;
    def->setBoolForKey("IS_ADS_ENABLE", isAdsEnable);
    removeAdsLabel->setString("Ads is removed");
    removeAdsItem->setEnabled(false);
    def->flush();
}
void SettingsScene::onFailure(sdkbox::Product const& p, const std::string &msg){}
void SettingsScene::onCanceled(sdkbox::Product const& p){}
void SettingsScene::onRestored(sdkbox::Product const& p)
{
    UserDefault* def = UserDefault::getInstance();
    isAdsEnable = false;
    def->setBoolForKey("IS_ADS_ENABLE", isAdsEnable);
    removeAdsLabel->setString("Ads is removed");
    removeAdsItem->setEnabled(false);
    def->flush();
}
void SettingsScene::onProductRequestSuccess(std::vector<sdkbox::Product> const &products){}
void SettingsScene::onProductRequestFailure(const std::string &msg){}
void SettingsScene::onRestoreComplete(bool ok, const std::string &msg){}
#endif
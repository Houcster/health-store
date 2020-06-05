#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

#ifdef SDKBOX_ENABLED
#include "PluginIAP/PluginIAP.h"
#endif

class SettingsScene : public cocos2d::Scene, public sdkbox::IAPListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void setSoundsEnabling(cocos2d::Ref* pSender);
    void setMusicEnabling(cocos2d::Ref* pSender);
    void removeAds(cocos2d::Ref* pSender);
    void restoreAds(cocos2d::Ref* pSender);
    void showMainMenu(cocos2d::Ref* pSender);

#ifdef SDKBOX_ENABLED
private:
    void onInitialized(bool ok);
    void onSuccess(sdkbox::Product const& p);
    void onFailure(sdkbox::Product const& p, const std::string &msg);
    void onCanceled(sdkbox::Product const& p);
    void onRestored(sdkbox::Product const& p);
    void onProductRequestSuccess(std::vector<sdkbox::Product> const &products);
    void onProductRequestFailure(const std::string &msg);
    void onRestoreComplete(bool ok, const std::string &msg);
#endif

// implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
};

#endif // __SETTINGS_SCENE_H__

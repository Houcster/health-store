#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

class GameOverScene : public cocos2d::Scene, public sdkbox::AdMobListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* gos_label;
    // a selector callback

    void restartGame(cocos2d::Ref* pSender);
    void continueGame(cocos2d::Ref* pSender);
    void continueGameByAds(cocos2d::Ref* pSender);
    void shareResults(cocos2d::Ref* pSender);
    void showMainMenu(cocos2d::Ref* pSender);

#ifdef SDKBOX_ENABLED
private:
    void adViewDidReceiveAd(const std::string &name);
    void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg);
    void adViewWillPresentScreen(const std::string &name);
    void adViewDidDismissScreen(const std::string &name);
    void adViewWillDismissScreen(const std::string &name);
    void adViewWillLeaveApplication(const std::string &name);
    void reward(const std::string &name, const std::string &currency, double amount);

#endif

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __GAMEOVER_SCEN
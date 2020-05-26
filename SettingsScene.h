#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* sc_soundLabel;
    cocos2d::Label* sc_musicLabel;
    // a selector callback
    void setSoundsEnabling(cocos2d::Ref* pSender);
    void setMusicEnabling(cocos2d::Ref* pSender);
    void showMainMenu(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
};

#endif // __SETTINGS_SCENE_H__

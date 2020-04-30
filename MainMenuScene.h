#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void createGamingScene(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAINMENU_SCENE_H__

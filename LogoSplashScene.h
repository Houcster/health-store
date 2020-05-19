#ifndef __LOGO_SPLASH_SCENE_H__
#define __LOGO_SPLASH_SCENE_H__

#include "cocos2d.h"

class LogoSplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* gos_label;
    // a selector callback
    void showMainMenu(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(LogoSplashScene);
};

#endif // __LOGO_SPLASH_SCENE_H__

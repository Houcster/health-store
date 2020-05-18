#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* gos_label;
    // a selector callback
    void createGamingScene(cocos2d::Ref* pSender);
    void shareResults(cocos2d::Ref* pSender);
    void showMainMenu(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __GAMEOVER_SCEN
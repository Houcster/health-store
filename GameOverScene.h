#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int score);

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void createGamingScene(cocos2d::Ref* pSender);
    void setScore(int score);
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif // __GAMEOVER_SCENE_H__
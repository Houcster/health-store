#ifndef __LEVEL_COMPLETE_SCENE_H__
#define __LEVEL_COMPLETE_SCENE_H__

#include "cocos2d.h"

class LevelCompleteScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Label* gos_label;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void createGamingScene(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(LevelCompleteScene);
};

#endif // __LEVEL_COMPLETE_SCENE_H__
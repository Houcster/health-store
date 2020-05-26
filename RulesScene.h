#ifndef __RULES_SCENE_H__
#define __RULES_SCENE_H__

#include "cocos2d.h"

class RulesScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void showMainMenu(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(RulesScene);
};

#endif // __RULES_SCENE_H__

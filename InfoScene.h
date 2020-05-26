#ifndef __INFO_SCENE_H__
#define __INFO_SCENE_H__

#include "cocos2d.h"

class InfoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void showMainMenu(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(InfoScene);
};

#endif // __INFO_SCENE_H__

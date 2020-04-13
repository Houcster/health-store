#ifndef __GAMING_SCENE_H__
#define __GAMING_SCENE_H__

#include "cocos2d.h"
#include "MyBodyParser.h"

class GamingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void changeLabelColor(cocos2d::Ref* pSender, cocos2d::Label* label);
    void goBack(cocos2d::Ref* pSender);

    bool onContactBegin(cocos2d::PhysicsContact& contact);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void createItem();
    void update(float dt);

protected:
    std::unordered_map<int, Node*> _mouses;
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamingScene);
};

#endif // __GAMING_SCENE_H__

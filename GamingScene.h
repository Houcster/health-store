#ifndef __GAMING_SCENE_H__
#define __GAMING_SCENE_H__

#include "cocos2d.h"
#include "MyBodyParser.h"

class GamingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    cocos2d::Label* gs_levelLabel;
    cocos2d::Label* gs_scoreLabel;
    // a selector callback 
    void update(float dt);
    void createItems(float dt);   
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);   
    void setRules();
    void playSound(int soundKey);
    void playBackgroundMusic();

protected:
    std::unordered_map<int, Node*> _mouses;
    std::set<Node*> nodesScheduledForRemoval;

    // implement the "static create()" method manually
    CREATE_FUNC(GamingScene);
};

#endif // __GAMING_SCENE_H__


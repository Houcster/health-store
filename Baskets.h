#ifndef __Sample__Basket__
#define __Sample__Basket__

#include "cocos2d.h"

class Basket : public cocos2d::Node
{
public:
    static Basket* createBasket(cocos2d::Layer* layer, cocos2d::Size* itemPos, int category);

    cocos2d::Sprite* spriteBack;
    cocos2d::Sprite* spriteForward;
    cocos2d::PhysicsBody* bodyBack;
    cocos2d::PhysicsBody* bodyForward;
};

#endif
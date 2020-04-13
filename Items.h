#ifndef __Sample__Item__
#define __Sample__Item__

#include "cocos2d.h"

class Item : public cocos2d::Node
{
public:
    static Item* createItem(cocos2d::Layer* layer, cocos2d::Size* itemPos);

    cocos2d::Sprite* sprite;
    cocos2d::PhysicsBody* body;
};

#endif
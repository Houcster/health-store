#ifndef __ITEMS__
#define __ITEMS__

#include "cocos2d.h"

class Item : public cocos2d::Node
{
public:
    static Item* createItem(cocos2d::Layer* layer);
    static Item* createBadItem(cocos2d::Layer* layer);

    cocos2d::Sprite* sprite;
    cocos2d::PhysicsBody* body;

    ~Item()
    {
        CCLOG("Destructor was called!");
    }
};

#endif // __ITEMS__
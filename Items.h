#ifndef __ITEMS__
#define __ITEMS__

#include "cocos2d.h"

class Item : public cocos2d::Node
{
public:
    static Item* createItem();
    static Item* createBadItem();

    cocos2d::Sprite* sprite;
    cocos2d::PhysicsBody* body;
};
#endif // __ITEMS__
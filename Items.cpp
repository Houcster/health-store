#include "Items.h"
#include "MyBodyParser.h"
#include "AppDelegate.h"

USING_NS_CC;

static const int DRAG_BODYS_TAG = 0x80;
extern Size visibleSize;
extern int currentLevel;
extern int itemCounter;
extern int badItemCounter;
extern float itemSpeed;

Item* Item::createItem()
{
    std::string fruits[4] = { "orange", "pineapple", "banana", "lemon" };
    std::string veggies[4] = { "beetroot", "tomat", "onion", "brokkoli" };
    std::string name;
    int collisionBitmask;

    int random = cocos2d::RandomHelper::random_int(1, 100);
    if (random >= 1 && random <= 50)
    {
        name = fruits[cocos2d::RandomHelper::random_int(0, itemCounter)];
        collisionBitmask = 3;
    }
    else if (random >= 51 && random <= 100)
    {
        name = veggies[cocos2d::RandomHelper::random_int(0, itemCounter)];
        collisionBitmask = 4;
    }


    auto item = new (std::nothrow) Item;
    if (item && item->init()) {
        item->autorelease();
        item->sprite = Sprite::createWithSpriteFrameName(name);
        item->sprite->setContentSize(Size(visibleSize.width * 0.105f, visibleSize.height * 0.185f));
        item->sprite->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.8);
        item->sprite->setGlobalZOrder(3);
        //item->sprite->setOpacity(70);

        if (MyBodyParser::getInstance()->parseJsonFile("PhysicsBodies.json"))
        {
            item->body = MyBodyParser::getInstance()->bodyFromJson(item->sprite, name, PHYSICSBODY_MATERIAL_DEFAULT);
            item->body->setTag(DRAG_BODYS_TAG);
            item->body->setCollisionBitmask(collisionBitmask);
            item->body->setContactTestBitmask(true);
            item->body->setDynamic(false);

            if (item->body != nullptr)
            {
                // ������������� ���� ��� �������
                item->sprite->addComponent(item->body);
            }
            else
            {
                CCLOG("Object.cpp spriteBody is nullptr");
            }
        }
        else
        {
            CCLOG("JSON file not found");
        }

        item->body->setVelocity(Vec2(itemSpeed, 0));

        item->addChild(item->sprite);
        //layer->addChild(item);
        return item;
    }
    else
    {
        CC_SAFE_RELEASE(item);
    }

    return item;
}

Item* Item::createBadItem()
{
    std::string badItems[1] = { "cigarettes" };
    std::string name;
    int collisionBitmask;

    name = badItems[cocos2d::RandomHelper::random_int(0, badItemCounter)];
    collisionBitmask = 6;

    auto item = new (std::nothrow) Item;
    if (item && item->init()) {
        item->autorelease();
        item->sprite = Sprite::createWithSpriteFrameName(name);
        item->sprite->setContentSize(Size(visibleSize.width * 0.105f, visibleSize.height * 0.185f));
        item->sprite->setPosition(visibleSize.width * 0.95f, visibleSize.height * 0.8);
        item->sprite->setGlobalZOrder(3);
        //item->sprite->setOpacity(40);

        if (MyBodyParser::getInstance()->parseJsonFile("PhysicsBodies.json"))
        {
            item->body = MyBodyParser::getInstance()->bodyFromJson(item->sprite, name, PHYSICSBODY_MATERIAL_DEFAULT);
            item->body->setTag(DRAG_BODYS_TAG);
            item->body->setCollisionBitmask(collisionBitmask);
            item->body->setContactTestBitmask(true);
            item->body->setDynamic(false);

            if (item->body != nullptr)
            {
                // ������������� ���� ��� �������
                item->sprite->addComponent(item->body);
            }
            else
            {
                CCLOG("Object.cpp spriteBody is nullptr");
            }
        }
        else
        {
            CCLOG("JSON file not found");
        }

        item->body->setVelocity(Vec2(itemSpeed, 0));

        item->addChild(item->sprite);
        //layer->addChild(item);
        return item;
    }
    else
    {
        CC_SAFE_RELEASE(item);
    }

    return item;
}


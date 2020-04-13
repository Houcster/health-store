#include "Items.h"
#include "MyBodyParser.h"

USING_NS_CC;

static const int DRAG_BODYS_TAG = 0x80;

Item* Item::createItem(Layer* layer, Size* itemPos)
{
    std::string fruits[2] = { "orange", "pineapple" };
    std::string veggies[2] = { "beetroot", "tomat" };
    std::string name;
    int collisionBitmask;

    int random = cocos2d::RandomHelper::random_int(1, 60);
    if (random >= 1 && random <= 30)
    {
        name = fruits[cocos2d::RandomHelper::random_int(0, 1)];
        collisionBitmask = 3;
    }
    else if (random >= 31 && random <= 60)
    {
        name = veggies[cocos2d::RandomHelper::random_int(0, 1)];
        collisionBitmask = 4;
    }


    auto item = new (std::nothrow) Item;
    if (item && item->init()) {
        item->autorelease();
        item->sprite = Sprite::createWithSpriteFrameName(name);
        item->sprite->setContentSize(Size(100.0f, 100.0f));
        item->sprite->setPosition(itemPos->width * 0.5, itemPos->height * 0.4);

        if (MyBodyParser::getInstance()->parseJsonFile("PhysicsBodies.json"))
        {


            item->body = MyBodyParser::getInstance()->bodyFromJson(item->sprite, name, PHYSICSBODY_MATERIAL_DEFAULT);
            item->body->setTag(DRAG_BODYS_TAG);
            item->body->setCollisionBitmask(collisionBitmask);
            item->body->setContactTestBitmask(true);

            if (item->body != nullptr)
            {
                // Устанавливаем тело для спрайта
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
        item->addChild(item->sprite);
        layer->addChild(item);
        return item;
    }
    CC_SAFE_RELEASE(item);
    return nullptr;
}


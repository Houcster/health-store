#include "Baskets.h"
#include "MyBodyParser.h"

USING_NS_CC;
extern Size visibleSize;

Basket* Basket::createBasket(Layer* layer, int category)
{
    Size position;
    std::string nameBack;
    std::string nameForward;
    int collisionBitmask;

    if (category == 1)
    {
        position = Size(visibleSize.width * 0.2f, visibleSize.height * 0.265f);
        nameBack = "fruitsBasketBack";
        nameForward = "fruitsBasketForward";
        collisionBitmask = 1;
    }
    else if (category == 2)
    {
        position = Size(visibleSize.width * 0.8f, visibleSize.height * 0.265f);
        nameBack = "veggiesBasketBack";
        nameForward = "veggiesBasketForward";
        collisionBitmask = 2;
    }
   
    auto basket = new (std::nothrow) Basket;
    if (basket && basket->init()) {

        basket->autorelease();

        basket->spriteBack = Sprite::createWithSpriteFrameName(nameBack);
        basket->spriteBack->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.445f));
        basket->spriteBack->setPosition(position);
        basket->spriteBack->setGlobalZOrder(2);
        //basket->spriteBack->setOpacity(20);
        basket->addChild(basket->spriteBack);

        basket->spriteForward = Sprite::createWithSpriteFrameName(nameForward);
        basket->spriteForward->setContentSize(Size(visibleSize.width * 0.25f, visibleSize.height * 0.445f));
        basket->spriteForward->setPosition(position);
        basket->spriteForward->setGlobalZOrder(4);
        //basket->spriteForward->setOpacity(20);
        basket->addChild(basket->spriteForward);

        if (MyBodyParser::getInstance()->parseJsonFile("PhysicsBodies.json"))
        {
            basket->bodyBack = MyBodyParser::getInstance()->bodyFromJson(basket->spriteBack, nameBack, PHYSICSBODY_MATERIAL_DEFAULT);
            basket->bodyBack->setContactTestBitmask(true);
            basket->bodyBack->setDynamic(false);

            basket->bodyForward = MyBodyParser::getInstance()->bodyFromJson(basket->spriteForward, nameForward, PHYSICSBODY_MATERIAL_DEFAULT);
            basket->bodyForward->setCollisionBitmask(collisionBitmask);
            basket->bodyForward->setContactTestBitmask(true);
            basket->bodyForward->setDynamic(false);

            if (basket->bodyBack != nullptr && basket->bodyForward != nullptr)
            {
                // Устанавливаем тело для спрайта
                basket->spriteBack->addComponent(basket->bodyBack);
                basket->spriteForward->addComponent(basket->bodyForward);
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

        layer->addChild(basket);
        return basket;
    }
    CC_SAFE_RELEASE(basket);
    return nullptr;
}
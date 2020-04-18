#include "GamingScene.h"
#include "Items.h"
#include "Baskets.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* scene;
static const int DRAG_BODYS_TAG = 0x80;
Size visibleSize;
Size itemsPos;
Label* label;
int score;


Scene* GamingScene::createScene()
{
    // create the scene with physics enabled
    scene = Scene::createWithPhysics();

    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

    // optional: set debug draw
    //scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

    auto layer = GamingScene::create();
    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GamingScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GamingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }

    LayerColor* _bgColor = LayerColor::create(Color4B(124, 130, 130, 255));
    this->addChild(_bgColor, -10);

    score = 0;
    visibleSize = Director::getInstance()->getVisibleSize();
    itemsPos = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    label = Label::createWithTTF("Its Gaming Scene", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    auto menu_item_1 = MenuItemFont::create("Back", CC_CALLBACK_1(GamingScene::goBack, this));

    menu_item_1->setPosition(visibleSize.width * 0.935f, visibleSize.height * 0.964f);

    auto* menu = Menu::create(menu_item_1, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    auto borderBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto borderNode = Node::create();
    borderNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    borderNode->setPhysicsBody(borderBody);
    addChild(borderNode);

    auto groundBody = PhysicsBody::createBox(Size(visibleSize.width, visibleSize.height * 0.03f), PHYSICSBODY_MATERIAL_DEFAULT);
    groundBody->setCollisionBitmask(5);
    groundBody->setContactTestBitmask(true);
    groundBody->setDynamic(false);

    auto groundNode = Node::create();
    groundNode->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.02f);
    groundNode->setPhysicsBody(groundBody);
    addChild(groundNode);


    auto barrierBody = PhysicsBody::createBox(Size(visibleSize.width * 0.015f, visibleSize.height * 0.52f), PHYSICSBODY_MATERIAL_DEFAULT);
    barrierBody->setCollisionBitmask(5);
    barrierBody->setContactTestBitmask(true);
    barrierBody->setDynamic(false);

    auto barrierSprite = Sprite::create("barrier.png");
    barrierSprite->setContentSize(Size(15.0f, 280.0f));
    barrierSprite->setPosition(visibleSize.width * 0.0075f, visibleSize.height * 0.925f);
    barrierSprite->addComponent(barrierBody);
    addChild(barrierSprite);

    auto fruitbasket = Basket::createBasket(this, &itemsPos, 1);
    auto veggiesbasket = Basket::createBasket(this, &itemsPos, 2);

    auto bodiesContactListener = EventListenerPhysicsContact::create();
    bodiesContactListener->onContactBegin = CC_CALLBACK_1(GamingScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bodiesContactListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GamingScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GamingScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    schedule(CC_SCHEDULE_SELECTOR(GamingScene::update), 1.8f);
  
    return true;
}

///////////////////////////////////////
//Далее идут все вспомогательные методы
///////////////////////////////////////

void GamingScene::update(float dt)
{
    auto item = Item::createItem(this, &itemsPos);
    //CCLOG("got");
}

bool GamingScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    Node* nodeA = a->getNode();
    Node* nodeB = b->getNode();

    if (nodeA && nodeB)
    {
        //Условие, при котором удаляются фрукты, если попали в корзину для фруктов
        //CollisionBitMask:
        //1 - корзина для фруктов
        //2 - корзина для овощей
        //3 - фрукты
        //4 - овощи
        //5 - барьер и земля
        if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 1)
        {
            nodeA->removeFromParentAndCleanup(true);
            score++;
            label->setString(std::to_string(score));
        }
        else if (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 3)
        {
            nodeB->removeFromParentAndCleanup(true);
            score++;
            label->setString(std::to_string(score));
        }

        //Условие, при котором удаляются овощи, если попали в корзину для овощей
        if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2)
        {
            nodeA->removeFromParentAndCleanup(true);
            score++;
            label->setString(std::to_string(score));
        }
        else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 4)
        {
            nodeB->removeFromParentAndCleanup(true);
            score++;
            label->setString(std::to_string(score));
        }

        //Условие, при котором игра заканчивается, если фрукт попал в корзину для овощей
        if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 1)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }
        else if (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 4)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }

        //Условие, при котором игра заканчивается, если овощь попал в корзину для фруктов
        if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 2)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }
        else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 3)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }

        if (a->getCollisionBitmask() == 5)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }
        else if (b->getCollisionBitmask() == 5)
        {
            auto GameOverScene = GameOverScene::createScene(score);
            Director::getInstance()->replaceScene(GameOverScene);
        }
    }
    //CCLOG("1");
    //CCLOG("2");
    return true;
}

bool GamingScene::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = scene->getPhysicsWorld()->getShapes(location);

    PhysicsBody* body = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & DRAG_BODYS_TAG) != 0)
        {
            body = obj->getBody();
            if (!body->isDynamic())
            {
                body->setDynamic(true);
            }
            break;
        }
    }

    if (body != nullptr)
    {
        Node* mouse = Node::create();
        mouse->setPhysicsBody(PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY));
        mouse->getPhysicsBody()->setDynamic(false);
        mouse->setPosition(location);
        this->addChild(mouse);
        auto joint = PhysicsJointPin::construct(mouse->getPhysicsBody(), body, location);
        joint->setMaxForce(5000.0f * body->getMass());
        scene->getPhysicsWorld()->addJoint(joint);
        _mouses.insert(std::make_pair(touch->getID(), mouse));

        return true;
    }

    return false;
}

void GamingScene::onTouchMoved(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());

    if (it != _mouses.end())
    {
        it->second->setPosition(touch->getLocation());
    }
}

void GamingScene::onTouchEnded(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());

    if (it != _mouses.end())
    {
        this->removeChild(it->second);
        _mouses.erase(it);
    }
}

void GamingScene::createItem()
{
    auto player = Item::createItem(this, &itemsPos);
}

void GamingScene::goBack(Ref* psender) 
{
    Director::getInstance()->popScene();
}

void GamingScene::changeLabelColor(Ref* pSender, Label* label)
{
    label->setTextColor(Color4B::YELLOW);
}

void GamingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

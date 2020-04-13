#include "GamingScene.h"
#include "Items.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static Scene* scene;
static const int DRAG_BODYS_TAG = 0x80;
static Size visibleSize;
static Size itemsPos;
static PhysicsBody* orange_physicsBody;
static Sprite* sprite_fruitOrange;
static PhysicsBody* tomat_physicsBody;
static Sprite* sprite_vegTomat;
static Label* label;
static PhysicsJointPin* joint;
static int score = 0;


Scene* GamingScene::createScene()
{
    // create the scene with physics enabled
    scene = Scene::createWithPhysics();

    // set gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0, -900));

    // optional: set debug draw
    scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

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

    menu_item_1->setPosition(visibleSize.width * 0.95, visibleSize.height * 0.05);

    auto* menu = Menu::create(menu_item_1, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    

    auto groundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto groundNode = Node::create();
    groundNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    groundNode->setPhysicsBody(groundBody);
    addChild(groundNode);

    auto fruitBasketBody = PhysicsBody::createBox(Size(100.0f, 20.0f), PHYSICSBODY_MATERIAL_DEFAULT);
    fruitBasketBody->setCollisionBitmask(1);
    fruitBasketBody->setContactTestBitmask(true);
    fruitBasketBody->setDynamic(false);

    auto fruitBasketNode = Node::create();
    fruitBasketNode->setPosition(visibleSize.width * 0.2, visibleSize.height * 0.1);
    fruitBasketNode->setPhysicsBody(fruitBasketBody);
    addChild(fruitBasketNode);

    auto vegBasketBody = PhysicsBody::createBox(Size(100.0f, 20.0f), PHYSICSBODY_MATERIAL_DEFAULT);
    vegBasketBody->setCollisionBitmask(2);
    vegBasketBody->setContactTestBitmask(true);
    vegBasketBody->setDynamic(false);

    auto vegBasketNode = Node::create();
    vegBasketNode->setPosition(visibleSize.width * 0.8, visibleSize.height * 0.1);
    vegBasketNode->setPhysicsBody(vegBasketBody);
    addChild(vegBasketNode);
    
    
    //auto orange_physicsBody = PhysicsBody::createBox(Size(100.0f, 100.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    //orange_physicsBody->setTag(DRAG_BODYS_TAG);

    //auto tomat_physicsBody = PhysicsBody::createBox(Size(100.0f, 100.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    //tomat_physicsBody->setTag(DRAG_BODYS_TAG);

    sprite_fruitOrange = Sprite::createWithSpriteFrameName("orange");
    sprite_fruitOrange->setContentSize(Size(100.0f, 100.0f));
    sprite_fruitOrange->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.4);
    addChild(sprite_fruitOrange);

    if (MyBodyParser::getInstance()->parseJsonFile("PhysicsBodies.json"))
    {
        //PhysicsMaterial(0.1f, 1.0f, 0.0f)
        orange_physicsBody = MyBodyParser::getInstance()->bodyFromJson(sprite_fruitOrange, "orange", PHYSICSBODY_MATERIAL_DEFAULT);
        orange_physicsBody->setTag(DRAG_BODYS_TAG);
        orange_physicsBody->setName("orangeBody");
        orange_physicsBody->setCollisionBitmask(3);
        orange_physicsBody->setContactTestBitmask(true);

        if (orange_physicsBody != nullptr)
        {
            // ”станавливаем тело дл€ спрайта
            sprite_fruitOrange->addComponent(orange_physicsBody);
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

    auto bodiesContactListener = EventListenerPhysicsContact::create();
    bodiesContactListener->onContactBegin = CC_CALLBACK_1(GamingScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bodiesContactListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GamingScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GamingScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    schedule(CC_SCHEDULE_SELECTOR(GamingScene::update), 2.0f);
  
    return true;
}

///////////////////////////////////////
//ƒалее идут все вспомогательные методы
///////////////////////////////////////

void GamingScene::update(float dt)
{
    auto player = Item::createItem(this, &itemsPos);
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
        //”словие, при котором удал€ютс€ фрукты, если попали в корзину дл€ фруктов
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

        //”словие, при котором удал€ютс€ овощи, если попали в корзину дл€ овощей
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
            if (!body->isGravityEnabled())
            {
            body->setGravityEnable(true);
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
        joint = PhysicsJointPin::construct(mouse->getPhysicsBody(), body, location);
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

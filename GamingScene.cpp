#include "GamingScene.h"
#include "Items.h"
#include "Baskets.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "LevelCompleteScene.h"
#include "AudioEngine.h"

USING_NS_CC;

static const int DRAG_BODYS_TAG = 0x80;
extern Size visibleSize;
extern int score;
extern int lives;
extern int currentLevel;
extern int levelDoneCount;
extern int itemCounter;
extern int badItemCounter;
extern float itemSpeed;
extern float itemSpawnFreq;

extern int inGameMusic;
extern bool isSoundsEnable;
extern bool isMusicEnable;

static bool musicSwitch;

Scene* GamingScene::createScene()
{
    // create the scene with physics enabled
    auto gamingScene = Scene::createWithPhysics();

    // set gravity
    gamingScene->getPhysicsWorld()->setGravity(Vec2(0, -900));

    // optional: set debug draw
    //gamingScene->getPhysicsWorld()->setDebugDrawMask(0xffff);

    auto layer = GamingScene::create();
    gamingScene->addChild(layer);
    gamingScene->getPhysicsWorld()->setSubsteps(10);

    return gamingScene;
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
    if (!Layer::init())
    {
        return false;
    }

    setRules();

    //LayerColor* _bgColor = LayerColor::create(Color4B(124, 130, 130, 255));
    //this->addChild(_bgColor, -10);

    auto gamingSceneBGSprite = Sprite::createWithSpriteFrameName("inGameBG");
    gamingSceneBGSprite->setContentSize(Size(visibleSize.width, visibleSize.height));
    gamingSceneBGSprite->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    addChild(gamingSceneBGSprite);

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    gs_levelLabel = Label::createWithTTF("Level: " + std::to_string(currentLevel), "fonts/arial.ttf", 24);
    if (gs_levelLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        gs_levelLabel->setPosition(Vec2(visibleSize.width * 0.05f, visibleSize.height * 0.964f));
        gs_levelLabel->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(gs_levelLabel, 1);
    }

    gs_scoreLabel = Label::createWithTTF(std::to_string(score), "fonts/arial.ttf", 24);
    if (gs_scoreLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        gs_scoreLabel->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.964f));
        gs_scoreLabel->setColor(Color3B::BLACK);
        // add the label as a child to this layer
        this->addChild(gs_scoreLabel, 1);
    }

    auto* menu = Menu::create(NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    //////////////////////////////////////////
    auto borderBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto borderNode = Node::create();
    borderNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    borderNode->setPhysicsBody(borderBody);
    addChild(borderNode);

    ////////////////////////////////////////////////////////////////////////////
    auto groundBody = PhysicsBody::createBox(Size(visibleSize.width, visibleSize.height * 0.03f), PHYSICSBODY_MATERIAL_DEFAULT);
    groundBody->setCollisionBitmask(5);
    groundBody->setContactTestBitmask(true);
    groundBody->setDynamic(false);

    auto groundNode = Node::create();
    groundNode->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.02f);
    groundNode->setPhysicsBody(groundBody);
    addChild(groundNode);

    ////////////////////////////////////////////////////////////////////////////
    auto barrierBody = PhysicsBody::createBox(Size(visibleSize.width * 0.07f, visibleSize.height * 0.52f), PHYSICSBODY_MATERIAL_DEFAULT);
    barrierBody->setCollisionBitmask(5);
    barrierBody->setContactTestBitmask(true);
    barrierBody->setDynamic(false);

    auto barrierNode = Node::create();
    barrierNode->setPosition(visibleSize.width * 0.0125f, visibleSize.height * 0.945f);
    barrierNode->addComponent(barrierBody);
    addChild(barrierNode);

    ////////////////////////////////////////////////////////////////////////////
    auto bgPatchBody = PhysicsBody::createBox(Size(visibleSize.width * 0.085f, visibleSize.height * 0.0155f), PHYSICSBODY_MATERIAL_DEFAULT);
    bgPatchBody->setDynamic(false);

    auto bgPatchNode = Node::create();
    bgPatchNode->setPosition(visibleSize.width * 0.9575f, visibleSize.height * 0.6805f);
    bgPatchNode->addComponent(bgPatchBody);
    addChild(bgPatchNode);

    auto bgPatchSprite = Sprite::createWithSpriteFrameName("gamingScenePatch");
    bgPatchSprite->setContentSize(Size(visibleSize.width * 0.085f, visibleSize.height * 0.245f));
    bgPatchSprite->setPosition(visibleSize.width * 0.9575f, visibleSize.height * 0.8055f);
    bgPatchSprite->setGlobalZOrder(20);
    addChild(bgPatchSprite);

    ////////////////////////////////////////////////////////////////////////////
    if (currentLevel < 4)
    {
        auto fruitbasket = Basket::createBasket(this, 1);
        auto veggiesbasket = Basket::createBasket(this, 2);
    }
    else
    {
        auto fruitbasket = Basket::createBasket(this, 3);
        auto veggiesbasket = Basket::createBasket(this, 4);
        auto recycle = Basket::createBasket(this, 5);
    }

    ////////////////////////////////////////////////////////////////////////////
    auto bodiesContactListener = EventListenerPhysicsContact::create();
    bodiesContactListener->onContactBegin = CC_CALLBACK_1(GamingScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bodiesContactListener, this);

    ////////////////////////////////////////////////////////////////////////////
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GamingScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GamingScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GamingScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    playBackgroundMusic();
    
    schedule(CC_SCHEDULE_SELECTOR(GamingScene::createItems), itemSpawnFreq);
    this->scheduleUpdate();

    
    return true;
}

///////////////////////////////////////
//Далее идут все вспомогательные методы
///////////////////////////////////////

void GamingScene::update(float dt)
{
    std::set<Node*>::iterator it = nodesScheduledForRemoval.begin();
    std::set<Node*>::iterator end = nodesScheduledForRemoval.end();
    for (; it != end; ++it) {
        Node* dyingNode = *it;

        //delete ball... physics body is destroyed here
        dyingNode->onExit();

    }

    //clear this list for next time
    nodesScheduledForRemoval.clear();
}

void GamingScene::createItems(float dt)
{
    if (currentLevel < 4)
    {
        Node* item = Item::createItem();
        this->addChild(item);
    }
    else
    {
        int random = cocos2d::RandomHelper::random_int(1, 100);
        if (random >= 1 && random <= 75)
        {
            Node* item = Item::createItem();
            this->addChild(item);
        }
        else if (random >= 76 && random <= 100)
        {
            Node* item = Item::createBadItem();
            this->addChild(item);
        }
    }
}

bool GamingScene::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    Node* nodeA = a->getNode();
    Node* nodeB = b->getNode();

    if (nodeA && nodeB)
    {

        //CollisionBitMask:
        //1 - корзина для фруктов
        //2 - корзина для овощей
        //3 - фрукты
        //4 - овощи
        //5 - барьер и земля
        //6 - мусор
        //7 - мусорка

        //Условие, при котором удаляются фрукты, если попали в корзину для фруктов
        if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 1)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(3);
        }
        else if (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 3)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(3);
        }
        //Условие, при котором удаляются овощи, если попали в корзину для овощей
        else if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(3);
        }
        else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 4)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(3);
        }
        //Условие, при котором удаляется мусор, если попал в мусорку
        else if (a->getCollisionBitmask() == 6 && b->getCollisionBitmask() == 7)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(4);
        }
        else if (a->getCollisionBitmask() == 7 && b->getCollisionBitmask() == 6)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            score++;
            gs_scoreLabel->setString(std::to_string(score));
            playSound(4);
        }
        //Условие, при котором игра заканчивается, если фрукт попал в корзину для овощей
        else if (a->getCollisionBitmask() != 4 && b->getCollisionBitmask() == 2)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() != 4)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        //Условие, при котором игра заканчивается, если в мусорку попало что-то не то
        else if (a->getCollisionBitmask() != 6 && b->getCollisionBitmask() == 7)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (a->getCollisionBitmask() == 7 && b->getCollisionBitmask() != 6)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (a->getCollisionBitmask() != 3 && b->getCollisionBitmask() == 1)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() != 3)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (a->getCollisionBitmask() == 5)
        {
            b->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeB);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }
        else if (b->getCollisionBitmask() == 5)
        {
            a->setContactTestBitmask(false);
            nodesScheduledForRemoval.insert(nodeA);
            lives -= 1;
            playSound(2);
            auto GameOverScene = GameOverScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, GameOverScene));
        }


        if (score == levelDoneCount)
        {
            playSound(1);
            auto LevelCompleteScene = LevelCompleteScene::createScene();
            Director::getInstance()->replaceScene(TransitionSlideInR::create(1, LevelCompleteScene));
        }

    }

    return true;
}

bool GamingScene::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);

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
        auto joint = PhysicsJointFixed::construct(mouse->getPhysicsBody(), body, location);
        joint->setMaxForce(4000.0f * body->getMass());
        this->getScene()->getPhysicsWorld()->addJoint(joint);
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
        it->second->getPhysicsBody()->setDynamic(true);
        nodesScheduledForRemoval.insert(it->second);
        _mouses.erase(it);
    }

    playBackgroundMusic();
}

void GamingScene::changeLabelColor(Ref* pSender, Label* label)
{
    label->setTextColor(Color4B::YELLOW);
}

void GamingScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GamingScene::setRules()
{
    switch (currentLevel) {
    case 1:
        levelDoneCount = 10;
        itemCounter = 1;
        itemSpeed = visibleSize.width * -0.1667f;
        itemSpawnFreq = 1.625f;
        break;
    case 2:
        levelDoneCount = 25;
        itemCounter = 2;
        itemSpeed = visibleSize.width * -0.17085f;
        itemSpawnFreq = 1.585f;
        break;
    case 3:
        levelDoneCount = 40;
        itemCounter = 3;
        itemSpeed = visibleSize.width * -0.175f;
        itemSpawnFreq = 1.547f;
        break;
    case 4:
        levelDoneCount = 60;
        itemCounter = 3;
        itemSpeed = visibleSize.width * -0.17915f;
        itemSpawnFreq = 1.511f;
        break;
    case 5:
        levelDoneCount = 85;
        itemCounter = 4;
        itemSpeed = visibleSize.width * -0.18335f;
        itemSpawnFreq = 1.477f;
        break;
    case 6:
        levelDoneCount = 115;
        itemCounter = 5;
        itemSpeed = visibleSize.width * -0.1875f;
        itemSpawnFreq = 1.444f;
        break;
    case 7:
        levelDoneCount = 150;
        itemCounter = 5;
        badItemCounter = 1;
        itemSpeed = visibleSize.width * -0.1925f;
        itemSpawnFreq = 1.412f;
        break;
    case 8:
        levelDoneCount = 190;
        itemCounter = 6;
        badItemCounter = 1;
        itemSpeed = visibleSize.width * -0.19575f;
        itemSpawnFreq = 1.382f;
        break;
    case 9:
        levelDoneCount = 235;
        itemCounter = 6;
        badItemCounter = 2;
        itemSpeed = visibleSize.width * -0.2f;
        itemSpawnFreq = 1.354f;
        break;
    case 10:
        levelDoneCount = 285;
        itemCounter = 7;
        badItemCounter = 2;
        itemSpeed = visibleSize.width * -0.20415f;
        itemSpawnFreq = 1.326f;
        break;
    case 11:
        levelDoneCount = 350;
        itemCounter = 7;
        badItemCounter = 3;
        itemSpeed = visibleSize.width * -0.2085f;
        itemSpawnFreq = 1.3f;
        break;
    }
}

void GamingScene::playSound(int soundKey)
{
    if (isSoundsEnable)
    {
        switch (soundKey) {
        case 1:
            experimental::AudioEngine::play2d("audio/winSound.mp3");
            break;
        case 2:
            experimental::AudioEngine::stop(inGameMusic);
            experimental::AudioEngine::play2d("audio/loseSound.mp3");
            break;
        case 3:
            experimental::AudioEngine::play2d("audio/basketSound.mp3");
            break;
        case 4:
            experimental::AudioEngine::play2d("audio/trashSound.mp3");
            break;
        }
    }
}

void GamingScene::playBackgroundMusic()
{
    if (isMusicEnable && experimental::AudioEngine::getState(inGameMusic) != experimental::AudioEngine::AudioState::PLAYING)
    {
        if (musicSwitch)
        {
            inGameMusic = experimental::AudioEngine::play2d("audio/mainMusic_2.mp3", false, 0.4f);
            musicSwitch = false;
        }
        else
        {
            inGameMusic = experimental::AudioEngine::play2d("audio/mainMusic_1.mp3", false, 0.4f);
            musicSwitch = true;
        }
        
    }
}



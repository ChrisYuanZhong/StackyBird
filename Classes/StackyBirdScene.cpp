#include "StackyBirdScene.h"
#include "NormalBrick.h"
#include "SpikeBrick.h"
#include "GarbageCollectionBrick.h"

#include "GameProperties.h"

USING_NS_CC;

StackyBirdScene::~StackyBirdScene()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second != nullptr)
		    delete it->second;
	}
}

Scene* StackyBirdScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = StackyBirdScene::create();
    //layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -980));

    return scene;
}

bool StackyBirdScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // Input Callbacks
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = CC_CALLBACK_2(StackyBirdScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(StackyBirdScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(StackyBirdScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(StackyBirdScene::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // Collision Callback
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StackyBirdScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // Schedule Update
    this->scheduleUpdate();

    // Scene Object Setup
    auto bird = new Bird(this);
    //m_gameObjects.insert(Bird::CreateBird(this));

    auto brick = new NormalBrick(this, Vec2(500, 425));

    auto spike = new SpikeBrick(this, Vec2(800, 225));

    auto garbageCollector = new GarbageCollectionBrick(this, Vec2(-310, 175));
    
    auto floor = Sprite::create("RoundedSquare.png");
    floor->setContentSize(Size(1000, 350));
    floor->setColor(cocos2d::Color3B::ORANGE);
    auto floorBody = PhysicsBody::createBox(floor->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));
    floorBody->setDynamic(false);
    floor->setPhysicsBody(floorBody);
    floor->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY() - 400);
    this->addChild(floor, 0);

    auto ceiling = Sprite::create("RoundedSquare.png");
    ceiling->setContentSize(Size(1000, 350));
    ceiling->setColor(cocos2d::Color3B::ORANGE);
    auto ceilingBody = PhysicsBody::createBox(ceiling->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 0.0f));
    ceilingBody->setDynamic(false);
    ceiling->setPhysicsBody(ceilingBody);
    ceiling->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY() + 400);
    this->addChild(ceiling, 0);

    return true;
}

void StackyBirdScene::update(float delta)
{
    ObstacleGenerator(delta);

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
		if (it->second != nullptr)
		    it->second->update(delta);
    }
}

void StackyBirdScene::PushGameObject(std::pair<cocos2d::PhysicsBody*, GameObject*> gameObjectPair)
{
	m_gameObjects.insert(gameObjectPair);
}

void StackyBirdScene::RemoveGameObject(cocos2d::PhysicsBody* body)
{
    GameObject* gameObject = m_gameObjects[body];
    if (gameObject != nullptr)
    {
		delete gameObject;
		m_gameObjects.erase(body);
	}
}

void StackyBirdScene::RemoveGameObject(GameObject* gameObject)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second == gameObject)
        {
			delete it->second;
			m_gameObjects.erase(it);
			break;
		}
	}
}

bool StackyBirdScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody * a = contact.getShapeA()->getBody();
    PhysicsBody * b = contact.getShapeB()->getBody();

    if (m_gameObjects.find(a) != m_gameObjects.end())
        m_gameObjects[a]->onContactBegin(contact, b);

    if (m_gameObjects.find(b) != m_gameObjects.end())
        m_gameObjects[b]->onContactBegin(contact, a);

    return true;
}

void StackyBirdScene::ObstacleGenerator(float delta)
{
    m_ObstacleTimer += delta;

    if (m_ObstacleTimer >= OBSTACLE_SPAWN_INTERVAL)
    {
        // Generate a group of obstacle bricks that can form walls
        std::vector<Vec2> positions;
        int numBricks = rand() % (MAX_OBSTACLE_BRICKS_PER_GROUP - MIN_OBSTACLE_BRICKS_PER_GROUP) + MIN_OBSTACLE_BRICKS_PER_GROUP;
        for (int i = 0; i < numBricks; i++)
        {
			float y = LOWEST_OBSTACLE_HEIGHT + (rand() % ((HIGHEST_OBSTACLE_HEIGHT - LOWEST_OBSTACLE_HEIGHT) / BIRD_SIZE)) * BIRD_SIZE;
			positions.push_back(Vec2(500, y));
		}

        for (int i = 0; i < numBricks; i++)
        {
		    new NormalBrick(this, positions[i]);
		}

        if ((float)rand() / RAND_MAX < SPIKE_SPAWN_CHANCE)
		{
            new SpikeBrick(this, Vec2(600, LOWEST_OBSTACLE_HEIGHT));
        }

		// Reset the obstacle timer
		m_ObstacleTimer = 0.0f;
	}
}

bool StackyBirdScene::onTouchBegan(Touch* touch, Event* event)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second != nullptr)
		    it->second->onTouchBegan(touch, event);
	}

    return true;
}

void StackyBirdScene::onTouchEnded(Touch* touch, Event* event)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second != nullptr)
            it->second->onTouchEnded(touch, event);
    }
}

void StackyBirdScene::onTouchMoved(Touch* touch, Event* event)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second != nullptr)
		    it->second->onTouchMoved(touch, event);
	}
}

void StackyBirdScene::onTouchCancelled(Touch* touch, Event* event)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        if (it->second != nullptr)
            it->second->onTouchCancelled(touch, event);
    }
}
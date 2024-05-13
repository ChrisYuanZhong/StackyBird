#include "Bird.h"

#include "StackyBirdScene.h"

Bird::Bird(cocos2d::Layer* layer)
{
	m_sprite = cocos2d::Sprite::create("RoundedSquare.png");

	m_sprite->setContentSize(cocos2d::Size(BIRD_SIZE, BIRD_SIZE));

	m_sprite->setColor(cocos2d::Color3B::YELLOW);

	auto birdBody = cocos2d::PhysicsBody::createBox(m_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 0.0f, 0.0f));
	birdBody->setRotationEnable(false);
	birdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	birdBody->setContactTestBitmask(true);

	m_sprite->setPhysicsBody(birdBody);

	m_sprite->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2,
				225));

	layer->addChild(m_sprite, 0);

	dynamic_cast<StackyBirdScene*>(layer)->PushGameObject(std::make_pair(m_sprite->getPhysicsBody(), this));
}

std::pair<cocos2d::PhysicsBody*, GameObject*> Bird::CreateBird(cocos2d::Layer* layer)
{
	Bird* bird = new Bird(layer);

	return std::make_pair(bird->m_sprite->getPhysicsBody(), bird);
}

Bird::~Bird()
{
	for (int i = 0; i < m_eggs.size(); i++)
	{
		if (m_eggs[i] != nullptr)
			delete m_eggs[i];
	}
}

bool Bird::CanSpawnEgg() const
{
	// Check if there is any physics body within the area above the bird
	
	// Check the upper left corner of the bird's position after jumping
	auto shapes = m_sprite->getParent()->getScene()->getPhysicsWorld()->getShapes(m_sprite->getBoundingBox().origin + cocos2d::Vec2(0, (2 * m_sprite->getContentSize().height) - 0.5f));
	
	// Check the upper right corner of the bird's position after jumping
	shapes.pushBack(m_sprite->getParent()->getScene()->getPhysicsWorld()->getShapes(m_sprite->getBoundingBox().origin + cocos2d::Vec2(m_sprite->getContentSize().width, (2 * m_sprite->getContentSize().height) - 0.5f)));

	return shapes.size() == 0;
}

void Bird::Death()
{
	m_bIsDead = true;

	m_sprite->setColor(cocos2d::Color3B::RED);

	m_sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(-200, 200));
	m_sprite->getPhysicsBody()->setRotationEnable(true);
	m_sprite->getPhysicsBody()->setAngularVelocity(1.0f);
}

void Bird::SpawnEgg()
{
	if (CanSpawnEgg())
	{
		// Move the bird up
		m_sprite->setPosition(cocos2d::Vec2(m_sprite->getPosition().x, m_sprite->getPosition().y + m_sprite->getContentSize().height));
		m_sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0, 0));

		// Create an egg
		cocos2d::Vec2 worldPosition = m_sprite->convertToWorldSpace(m_sprite->getPosition());
		m_eggs.push_back(new Egg(dynamic_cast<cocos2d::Layer*>(m_sprite->getParent()), m_sprite->getPosition() - cocos2d::Vec2(0, m_sprite->getContentSize().height)));
	}
}

void Bird::onTouchBegan(cocos2d::Touch*, cocos2d::Event*)
{
	if (!m_bIsDead)
		SpawnEgg();
}

void Bird::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
}

void Bird::onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::PhysicsBody* other)
{
	// If the contanct normal is horizontal, then the bird is crashed
	if (other->getCollisionBitmask() == NORMAL_OBSTACLE_COLLISION_BITMASK && contact.getContactData()->normal.y == 0)
	{
		Death();
	}
	else if (other->getCollisionBitmask() == SPIKE_OBSTACLE_COLLISION_BITMASK)
	{
		Death();
	}
}

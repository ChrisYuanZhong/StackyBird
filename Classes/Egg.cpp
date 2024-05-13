#include "Egg.h"

#include "StackyBirdScene.h"

Egg::Egg(cocos2d::Layer* layer, const cocos2d::Vec2 position)
{
	m_sprite = cocos2d::Sprite::create("RoundedSquare.png");

	m_sprite->setContentSize(cocos2d::Size(50, 50));

	auto eggBody = cocos2d::PhysicsBody::createBox(m_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 0.0f, 0.0f));
	eggBody->setRotationEnable(false);
	eggBody->setCollisionBitmask(EGG_COLLISION_BITMASK);
	eggBody->setContactTestBitmask(true);

	m_sprite->setPhysicsBody(eggBody);

	m_sprite->setPosition(position);

	layer->addChild(m_sprite, 0);

	dynamic_cast<StackyBirdScene*>(layer)->PushGameObject(std::make_pair(m_sprite->getPhysicsBody(), this));
}

void Egg::Break()
{
	StackyBirdScene* scene = dynamic_cast<StackyBirdScene*>(m_sprite->getParent());

	m_sprite->removeFromParent();

	if (scene != nullptr)
		scene->RemoveGameObject(m_sprite->getPhysicsBody());
}

void Egg::onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::PhysicsBody* other)
{
	if (other->getCollisionBitmask() == SPIKE_OBSTACLE_COLLISION_BITMASK)
	{
		Break();
	}
}
#include "ObstacleBrick.h"

#include "StackyBirdScene.h"

ObstacleBrick::ObstacleBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position)
{
	m_sprite = cocos2d::Sprite::create("RoundedSquare.png");

	m_sprite->setContentSize(cocos2d::Size(OBSTACLE_BRICK_SIZE, OBSTACLE_BRICK_SIZE));
	m_sprite->setColor(cocos2d::Color3B::ORANGE);

	auto brickBody = cocos2d::PhysicsBody::createBox(m_sprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 0.0f, 0.0f));
	brickBody->setRotationEnable(false);
	brickBody->setDynamic(false);
	brickBody->setVelocity(cocos2d::Vec2(-OBSTACLE_SPEED, 0));
	brickBody->setCollisionBitmask(NORMAL_OBSTACLE_COLLISION_BITMASK);
	brickBody->setContactTestBitmask(true);

	m_sprite->setPhysicsBody(brickBody);

	m_sprite->setPosition(position + cocos2d::Vec2(0, 1.5f));	// Because the bird bricks cannot perfectly align with the obstacle bricks due to the physics engine

	layer->addChild(m_sprite, 0);

	dynamic_cast<StackyBirdScene*>(layer)->PushGameObject(std::make_pair(m_sprite->getPhysicsBody(), this));
}

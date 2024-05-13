#include "NormalBrick.h"

#include "StackyBirdScene.h"

NormalBrick::NormalBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position) : ObstacleBrick(layer, position)
{
	m_sprite->setColor(cocos2d::Color3B::ORANGE);

	m_sprite->getPhysicsBody()->setCollisionBitmask(NORMAL_OBSTACLE_COLLISION_BITMASK);
}

#include "SpikeBrick.h"

SpikeBrick::SpikeBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position) : ObstacleBrick(layer, position)
{
	m_sprite->setColor(cocos2d::Color3B::GRAY);

	m_sprite->getPhysicsBody()->setCollisionBitmask(SPIKE_OBSTACLE_COLLISION_BITMASK);
}
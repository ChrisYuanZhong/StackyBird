#include "GarbageCollectionBrick.h"

GarbageCollectionBrick::GarbageCollectionBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position) : SpikeBrick(layer, position)
{
	m_sprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0, 0));
	m_sprite->getPhysicsBody()->setCollisionBitmask(GARBAGE_COLLECTION_COLLISION_BITMASK);
}

#pragma once

#include "Bird.h"

inline bool Bird::CanSpawnEgg() const
{
	// Check if there is any physics body within the area above the bird

	// Check the upper left corner of the bird's position after jumping
	auto shapes = m_sprite->getParent()->getScene()->getPhysicsWorld()->getShapes(m_sprite->getBoundingBox().origin + cocos2d::Vec2(0, (2 * m_sprite->getContentSize().height) - 0.5f));

	// Check the upper right corner of the bird's position after jumping
	shapes.pushBack(m_sprite->getParent()->getScene()->getPhysicsWorld()->getShapes(m_sprite->getBoundingBox().origin + cocos2d::Vec2(m_sprite->getContentSize().width, (2 * m_sprite->getContentSize().height) - 0.5f)));

	return shapes.size() == 0;
}
#pragma once

#include "GameObject.h"

class ObstacleBrick : public GameObject
{
public:
	ObstacleBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position);

protected:
	cocos2d::Sprite* m_sprite;
};
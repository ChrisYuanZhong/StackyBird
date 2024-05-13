#pragma once

#include "ObstacleBrick.h"

class SpikeBrick : public ObstacleBrick
{
public:
	SpikeBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position);
};
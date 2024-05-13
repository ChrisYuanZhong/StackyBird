#pragma once

#include "ObstacleBrick.h"

class NormalBrick : public ObstacleBrick
{
public:
	NormalBrick(cocos2d::Layer* layer, const cocos2d::Vec2 position);
};
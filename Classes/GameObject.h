#pragma once

#include "cocos2d.h"

#include "GameProperties.h"

class GameObject
{
public:
	virtual void onTouchBegan(cocos2d::Touch*, cocos2d::Event*) {};
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) {};
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*) {};
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*) {};

	virtual void update(float) {};

	virtual void onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::PhysicsBody* other) {};
};
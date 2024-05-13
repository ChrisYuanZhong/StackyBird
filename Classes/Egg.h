#pragma once

#include "GameObject.h"

class Egg : public GameObject
{
public:
	Egg(cocos2d::Layer* layer, const cocos2d::Vec2 position);

	void Break();

	void onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::PhysicsBody* other) override;

private:
	cocos2d::Sprite* m_sprite;

	bool m_bIsBroken = false;
};
#pragma once

#include "GameObject.h"

#include "Egg.h"

class Bird : public GameObject
{
public:
	Bird(cocos2d::Layer *layer);
	static std::pair<cocos2d::PhysicsBody*, GameObject*> CreateBird(cocos2d::Layer* layer);
	~Bird();

	bool CanSpawnEgg() const;
	void Death();

	void onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) override;

	void onContactBegin(cocos2d::PhysicsContact& contact, cocos2d::PhysicsBody* other) override;

private:
	void SpawnEgg();

	cocos2d::Sprite* m_sprite;

	std::vector<Egg*> m_eggs;

	bool m_bIsDead = false;
	bool m_bShootyMode = true;
};
#pragma once

#include "cocos2d.h"

#include "GameProperties.h"

#include "GameObject.h"

#include "Bird.h"

class StackyBirdScene : public cocos2d::Layer
{
public:
    ~StackyBirdScene();

    static cocos2d::Scene* createScene();
    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    CREATE_FUNC(StackyBirdScene);

    void update(float) override;

    void PushGameObject(std::pair<cocos2d::PhysicsBody*, GameObject*> gameObjectPair);
    void RemoveGameObject(cocos2d::PhysicsBody* body);
    void RemoveGameObject(GameObject* gameObject);

private:
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    void ObstacleGenerator(float delta);
    float m_ObstacleTimer = 0.0f;

    std::unordered_map<cocos2d::PhysicsBody*, GameObject*> m_gameObjects;
};
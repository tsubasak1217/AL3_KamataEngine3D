#pragma once
#include "Object.h"
#include <list>
#include <memory>

class Player;
class Enemy;

class CollisionManager{

public:
	CollisionManager() = default;
	void CheckCollision();

public:
	std::list<Object*>colliders_;
	std::list<std::shared_ptr<Enemy>>* pEnemy_;
	Player* pPlayer_ = nullptr;
private:
	void CheckCollisionPair(Object* obj1, Object* obj2);
	void CheckReticleCollision();

public:
	void SetColliders(std::list<Object*>colliders){ colliders_ = colliders; }
	void PushBackCollider(Object* collider);
};
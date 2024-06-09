#pragma once
#include "Object.h"
#include <list>

class CollisionManager{

public:
	CollisionManager() = default;
	void CheckCollision();

public:
	std::list<Object*>colliders_;

private:
	void CheckCollisionPair(Object* obj1, Object* obj2);

public:
	void SetColliders(std::list<Object*>colliders){ colliders_ = colliders; }
	void PushBackCollider(Object* collider);
};
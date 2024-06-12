#pragma once
#include "Model.h"
#include "Object.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Bullet : public Object {
public:
	Bullet();
	Bullet(const Vector3& pos,const Vector3& rotate,const Vector3& moveVec,Object* homingObjectPtr = nullptr);
	~Bullet();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
	Object* homingObjectPtr_ = nullptr;

private:
	const int32_t kLifetime_ = 60 * 5;
	int32_t deathTimer_;
	float homingLevel_;
	Vector3 prePos_;

private:
	void Homing();

public:
	void OnCollision()override;

public:
	const bool GetIsAlive()const { return deathTimer_ > 0; }
	void SetHomingObject(Object* objectPtr){ homingObjectPtr_ = objectPtr; }
	void SetScale(const Vector3& scale){ scale_ = scale; }
};

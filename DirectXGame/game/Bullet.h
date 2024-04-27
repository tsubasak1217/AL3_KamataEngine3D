#pragma once
#include "Model.h"
#include "Object.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Bullet : public Object {
public:
	Bullet(const Vector3& pos,const Vector3& rotate,const Vector3& moveVec);
	~Bullet();
	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;
	void Fin() override;

private:
	const int32_t kLifetime_ = 60 * 5;
	int32_t deathTimer_;

public:
	void OnCollision();

public:
	bool GetIsAlive() { return deathTimer_ > 0; }
};

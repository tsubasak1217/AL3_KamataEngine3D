#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"
#include <vector>

class RailCamera{
public:
	RailCamera(Vector3 pos, Vector3 rotate);
	~RailCamera();
	void Init(Vector3 pos, Vector3 rotate);
	void Update();
	void Draw();
	void Fin();

private:
	WorldTransform wt_;
	ViewProjection vp_;
	Vector3 moveVec_;
	float moveSpeed_;
	Vector3 rotate_;

	// 制御点
	std::vector<Vector3>controlPoints_;
	Vector3 targetPoint_;
	float rail_t_ = 0.0f;
	float addRate_;
	float targetDistance_;

public:
	ViewProjection* GetViewProjection(){ return &vp_; }
	WorldTransform* GetWorldTransform(){ return &wt_; }
};
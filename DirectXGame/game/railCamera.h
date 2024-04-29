#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"

class RailCamera{
public:
	RailCamera(Vector3 pos, Vector3 rotate);
	~RailCamera();
	void Init(Vector3 pos, Vector3 rotate);
	void Update();
	void Fin();

private:
	WorldTransform wt_;
	ViewProjection vp_;
	Vector3 moveVec_;
	float moveSpeed_;
	Vector3 rotate_;

public:
	ViewProjection* GetViewProjection(){ return &vp_; }
	WorldTransform* GetWorldTransform(){ return &wt_; }
};
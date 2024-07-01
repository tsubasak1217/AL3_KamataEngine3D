#pragma once
#include "Vector3.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Camera{

public:
	Camera();
	~Camera();

protected:
	WorldTransform wt_;
	WorldTransform viewWt_;
	ViewProjection vp_;

public:
	void UpdateCamera();

public:
	ViewProjection* GetViewProjection(){ return &vp_; }
	WorldTransform* GetWorldTransform(){ return &wt_; }
	void SetWorldTransform(const WorldTransform& wt){ 
		wt_.scale_ = wt.scale_; 
		wt_.rotation_ = wt.rotation_;
		wt_.translation_ = wt.translation_;
	}
};
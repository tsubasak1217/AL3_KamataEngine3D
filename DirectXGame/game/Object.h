#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "Vector3.h"
#include "WorldTransform.h"

class Object {

public:
	Object();
	~Object();
	virtual void Init();
	virtual void Update();
	virtual void Draw(const ViewProjection& vp);
	virtual void Fin();

protected:
	//
	Vector3 pos_;

	//
	float radius_;
	float moveSpeed_;
	Vector3 moveVec_;

	//
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;

	//
	std::unique_ptr<Model> model_ = nullptr;
	WorldTransform wt_;

	//
	int GH_;

public:

	WorldTransform& GetWorldTransform() { return wt_; }
	Model* GetModel() { return model_.get(); }
	void SetModel(Model* model) { model_.reset(model); }
	float GetRadius()const{ return radius_; }
	void SetParentPtr(const WorldTransform* parentWt){ wt_.parent_ = parentWt; }
};

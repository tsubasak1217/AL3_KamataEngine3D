#pragma once
#include "Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"

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
	    Model* model_ = nullptr;
	    WorldTransform wt_;

		//
	    int GH_;

};

#pragma once
#include "Model.h"
#include "Object.h"
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Bullet : public Object {
public:
	Bullet(Vector3 pos);
	~Bullet();
	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;
	void Fin()override;

public:
	void SetModel(Model* model) { model_ = model; }
};

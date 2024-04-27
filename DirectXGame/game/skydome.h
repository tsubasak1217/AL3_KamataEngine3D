#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <memory>

class Skydome{
public:
	Skydome();
	~Skydome();
	void Init();
	void Update();
	void Draw(const ViewProjection& vp);
	void Fin();

private:
	WorldTransform wt_;
	std::unique_ptr<Model>model_;
};
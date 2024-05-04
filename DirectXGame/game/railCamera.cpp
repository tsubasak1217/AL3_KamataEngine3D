#include "railCamera.h"
#include "MyFunc.h"
#include  <ImGui.h>

RailCamera::RailCamera(Vector3 pos, Vector3 rotate)
{
	Init(pos, rotate);
}

RailCamera::~RailCamera()
{
	Fin();
}

void RailCamera::Init(Vector3 pos, Vector3 rotate)
{
	wt_.Initialize();
	wt_.translation_ = pos;
	wt_.rotation_ = rotate;
	vp_.Initialize();

	moveVec_ = {0.0f,0.0f,1.0f};
	moveSpeed_ = 0.125f; 
	rotate_ = {0.0f,0.0f,0.0f};
}

void RailCamera::Update()
{

#ifdef _DEBUG

	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("translate", &wt_.translation_.x, 0.25f);
	ImGui::DragFloat3("rotate", &wt_.rotation_.x, float(M_PI) * 0.005f);
	ImGui::End();

#endif // _DEBUG

	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ += rotate_;
	wt_.UpdateMatrix();

	vp_.matView = InverseMatrix(wt_.matWorld_);
	vp_.TransferMatrix();
}

void RailCamera::Fin()
{
}

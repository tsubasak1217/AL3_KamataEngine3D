#include "railCamera.h"
#include "MyFunc.h"
#include "PrimitiveDrawer.h"
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
	viewWt_.Initialize();
	vp_.Initialize();

	moveVec_ = { 0.0f,0.0f,1.0f };
	moveSpeed_ = 0.125f;
	rotate_ = { 0.0f,0.0f,0.0f };

	// 制御点
	controlPoints_.push_back({ 0.0f,  0.0f,  0.0f });
	controlPoints_.push_back({ 50.0f, 50.0f, 25.0f });
	controlPoints_.push_back({ 50.0f, 75.0f, 50.0f });
	controlPoints_.push_back({ 100.0f, 75.0f, 25.0f });
	controlPoints_.push_back({ 100.0f, 0.0f,  -25.0f });
	controlPoints_.push_back({ 150.0f, 0.0f,  0.0f });
	controlPoints_.push_back({ 50.0f,  -30.0f,  0.0f });
	controlPoints_.push_back({ 0.0f,  0.0f,  0.0f });

	rail_t_ = 0.0f;
	targetDistance_ = 0.02f;
	addRate_ = 0.0005f;

	// カメラの初期位置
	wt_.translation_ = CatmullRom(controlPoints_, rail_t_);
	// 初期注目点
	targetPoint_ = CatmullRom(controlPoints_, rail_t_ * 0.1f);

	// 軌道に合わせて回転
	Vector3 dif = Normalize(targetPoint_ - wt_.translation_);
	wt_.rotation_ = {
	std::atan2(-dif.y, Length(dif)),// 縦方向の回転角(X軸回り)
	std::atan2(dif.x, dif.z),// 横方向の回転角(Y軸回り)
	0.0f
	};

	// レール位置を引きで見る
	viewWt_.translation_ = wt_.translation_ - (dif * 20.0f);
	viewWt_.rotation_ = wt_.rotation_;
	viewWt_.scale_ = wt_.scale_;
}

void RailCamera::Update()
{

#ifdef _DEBUG

	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("translate", &wt_.translation_.x, 0.25f);
	ImGui::DragFloat3("rotate", &wt_.rotation_.x, float(M_PI) * 0.005f);
	ImGui::DragFloat("t_addRate", &addRate_, 0.005f);
	ImGui::DragFloat("tarGetDistance", &targetDistance_, 0.005f);
	ImGui::DragFloat("t", &rail_t_, 0.005f);
	ImGui::End();

#endif // _DEBUG

	// カメラの位置
	wt_.translation_ = CatmullRom(controlPoints_, rail_t_);
	// 注目点
	targetPoint_ = CatmullRom(controlPoints_, rail_t_ + targetDistance_);

	// 軌道に合わせて回転
	Vector3 dif = Normalize(targetPoint_ - wt_.translation_);
	wt_.rotation_ = {
	std::atan2(-dif.y, Length(dif)),// 縦方向の回転角(X軸回り)
	std::atan2(dif.x, dif.z),// 横方向の回転角(Y軸回り)
	0.0f
	};

	// レール位置を引きで見る
	viewWt_.translation_ = wt_.translation_ - (dif * 20.0f);
	viewWt_.rotation_ = wt_.rotation_;
	viewWt_.scale_ = wt_.scale_;
	viewWt_.UpdateMatrix();

	//wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ += rotate_;
	wt_.UpdateMatrix();


	vp_.matView = InverseMatrix(viewWt_.matWorld_);
	vp_.TransferMatrix();

	rail_t_ += addRate_;
	if(rail_t_ > 1.0f){ rail_t_ = 0.0f; }
}

void RailCamera::Draw(){
	DrawSpline3D(controlPoints_, 64);
}

void RailCamera::Fin()
{
}

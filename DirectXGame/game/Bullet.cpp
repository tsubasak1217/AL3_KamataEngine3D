#include "Bullet.h"

Bullet::Bullet(Vector3 pos) {
	wt_.Initialize();
	wt_.translation_ = pos;
	Init();
}

Bullet::~Bullet() { Fin(); }

void Bullet::Init() {
	model_ = Model::Create();
	scale_ = {1.0f, 1.0f, 1.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, 0.0f};
	GH_ = TextureManager::Load("uvChecker.png");
}

void Bullet::Update() {

// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_;
	wt_.rotation_ = rotate_;

	// ワールド行列の作成
 	wt_.UpdateMatrix();
}

void Bullet::Draw(const ViewProjection& vp) { 
	model_->Draw(wt_, vp, GH_); }

void Bullet::Fin() { 
	delete model_;
	model_ = nullptr;
}

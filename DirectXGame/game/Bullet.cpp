﻿#include "Bullet.h"
#include "MyFunc.h"

Bullet::Bullet(const Vector3& pos, const Vector3& rotate, const Vector3& moveVec) {
	Init();
	wt_.Initialize();
	wt_.translation_ = pos;
	wt_.rotation_ = rotate;
	moveVec_ = Normalize(moveVec);
}

Bullet::~Bullet() { Fin(); }

void Bullet::Init() {
	//model_ = std::make_unique<Model>();
	model_.reset(Model::Create());
	scale_ = {1.0f, 1.0f, 1.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, 1.0f};
	GH_ = TextureManager::Load("uvChecker.png");
	deathTimer_ = kLifetime_;
	moveSpeed_ = 2.0f;
}

void Bullet::Update() {

	// 寿命
	deathTimer_--;

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ += rotate_;

	// ワールド行列の作成
	wt_.UpdateMatrix();
}

void Bullet::Draw(const ViewProjection& vp) { model_->Draw(wt_, vp, GH_); }

void Bullet::Fin() {
	model_.reset();
}

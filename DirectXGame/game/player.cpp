﻿#include "player.h"
#include "MyFunc.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
const float PI = std::numbers::pi_v<float>;

Player::Player() { Init(); }

Player::~Player() {
	delete model_;
	model_ = nullptr;
	for (int i = 0; i < bullets_.size(); i++) {
		delete bullets_[i];
		bullets_[i] = nullptr;
	}
}

void Player::Init() {

	input_ = Input::GetInstance();
	model_ = new Model();
	model_->Create();
	wt_.Initialize();
	scale_ = {1.0f, 1.0f, 1.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, 0.0f};
	moveSpeed_ = 0.2f;
	GH_ = TextureManager::Load("uvChecker.png");
}

void Player::Update() {

	// 弾の発射
	Shoot();

	// 移動量の決定
	Move();

	// 回転
	Rotate();

	for (int i = 0; i < bullets_.size(); i++) {
		bullets_[i]->Update();
	}

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_;
	wt_.rotation_ = rotate_;

	// 移動制限
	wt_.translation_.x = std::clamp(wt_.translation_.x, -33.0f, 33.0f);
	wt_.translation_.y = std::clamp(wt_.translation_.y, -18.0f, 18.0f);

	// ワールド行列の作成
	wt_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& vp) {

	model_->Draw(wt_, vp, GH_);

	for (int i = 0; i < bullets_.size(); i++) {
		bullets_[i]->Draw(vp);
	}
}

void Player::Shoot() {

	if (input_->TriggerKey(DIK_SPACE)) {

		bullets_.push_back(new Bullet(wt_.translation_));
	}
}

void Player::Rotate() {

	if (input_->PushKey(DIK_A)) {
		rotate_.y += std::sin((1.0f / 128.0f) * PI);
	}

	if (input_->PushKey(DIK_D)) {
		rotate_.y -= std::sin((1.0f / 128.0f) * PI);
	}
}

void Player::Move() {

	// 移動量の初期化
	moveVec_ = {0.0f, 0.0f, 0.0f};

	// X軸の移動量決定
	if (input_->PushKey(DIK_LEFT)) {
		moveVec_.x -= moveSpeed_;
	}

	if (input_->PushKey(DIK_RIGHT)) {
		moveVec_.x += moveSpeed_;
	}

	// Y軸の移動量決定
	if (input_->PushKey(DIK_UP)) {
		moveVec_.y += moveSpeed_;
	}

	if (input_->PushKey(DIK_DOWN)) {
		moveVec_.y -= moveSpeed_;
	}
}

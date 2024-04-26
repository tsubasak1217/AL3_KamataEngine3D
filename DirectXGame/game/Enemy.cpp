#include "Enemy.h"
#include "MyFunc.h"
#include "player.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
const float PI = std::numbers::pi_v<float>;

Enemy::Enemy() { Init(); }

Enemy::~Enemy() {
	model_.reset();

	for(auto& bullet : bullets_) {
		bullet.reset();
	}
	bullets_.clear();
}

void Enemy::Init() {

	model_ = std::make_unique<Model>();
	wt_.Initialize();
	scale_ = { 1.0f, 1.0f, 1.0f };
	rotate_ = { 0.0f, PI, 0.0f };
	moveVec_ = { 0.0f, 0.0f, -1.0f };
	wt_.translation_ = { 4.0f, 1.5f, 20.0f };
	moveSpeed_ = 0.2f;
	action_ = APPROACH;
	frameCount_ = 0;
	GH_ = TextureManager::Load("symmetryORE_STRONG.jpg");
}

void Enemy::Update() {

	frameCount_++;

	// 弾の更新
	UpdateBullet();

	// 移動量の決定
	Translate();

	// 回転量の決定
	Rotate();


	// 実際に移動
	Move();

	// ワールド行列の作成
	wt_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& vp) {

	model_->Draw(wt_, vp, GH_);

	for(auto& bullet : bullets_) {
		bullet->Draw(vp);
	}
}

void Enemy::UpdateBullet() {

	switch(action_) {
	case APPROACH:

		// 一定時間経過した弾の削除
		std::erase_if(bullets_, [](auto& bullet) { return !(bullet->GetIsAlive()); });

		// 一定時間ごとに弾を発射
		if(frameCount_ % 30 == 0) {
			bullets_.push_back(std::make_unique<Bullet>(
				wt_.translation_,// 初期座標
				wt_.rotation_,// 初期回転値
				playerPtr_->GetWorldTransform().translation_ - wt_.translation_// 動くベクトル
			));
		}

		// 弾の更新
		for(auto& bullet : bullets_) {
			bullet->Update();
		}

		break;

	case EXIT:
		break;

	default:
		break;
	}
}

void Enemy::Rotate() {}

void Enemy::Translate() {
	switch(action_) {
	case APPROACH:

		break;

	case EXIT:
		break;

	default:
		break;
	}
}

void Enemy::Move() {

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ = rotate_;
}

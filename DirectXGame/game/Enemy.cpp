#include "Enemy.h"
#include "MyFunc.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
const float PI = std::numbers::pi_v<float>;

Enemy::Enemy() { Init(); }

Enemy::~Enemy() {
	delete model_;
	model_ = nullptr;
	for (Bullet* bullet : bullets_) {
		delete bullet;
		bullet = nullptr;
	}
}

void Enemy::Init() {

	model_ = new Model();
	model_->Create();
	wt_.Initialize();
	scale_ = {1.0f, 1.0f, 1.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, -1.0f};
	wt_.translation_ = {0.0f, 1.5f, 20.0f};
	moveSpeed_ = 0.2f;
	action_ = APPROACH;
	GH_ = TextureManager::Load("symmetryORE_STRONG.jpg");
}

void Enemy::Update() {

	// 弾の発射
	Shoot();

	// 移動量の決定
	Translate();

	// 回転量の決定
	Rotate();

	// 一定時間経過した弾の削除
	std::erase_if(bullets_, [](Bullet* bullet) { return !(bullet->GetIsAlive()); });

	// 弾の更新
	for (Bullet* bullet : bullets_) {
		bullet->Update();
	}

	// 実際に移動
	Move();

	// ワールド行列の作成
	wt_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& vp) {

	model_->Draw(wt_, vp, GH_);

	for (Bullet* bullet : bullets_) {
		bullet->Draw(vp);
	}
}

void Enemy::Shoot() {

	/*if (input_->TriggerKey(DIK_SPACE)) {
	    bullets_.push_back(new Bullet(wt_.translation_, wt_.rotation_));
	}*/
}

void Enemy::Rotate() {}

void Enemy::Translate() {
	switch (action_) {
	case APPROACH:
		
		if (wt_.translation_.z <= 0.0f) {
			action_ = EXIT;
			moveVec_ = Normalize({-1.0f, 1.0f, 0.0f});
		}
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

	// 移動制限
	// wt_.translation_.x = std::clamp(wt_.translation_.x, -33.0f, 33.0f);
	// wt_.translation_.y = std::clamp(wt_.translation_.y, -18.0f, 18.0f);
}

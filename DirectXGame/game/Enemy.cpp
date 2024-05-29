#include "Enemy.h"
#include "MyFunc.h"
#include "player.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
#include "GameScene.h"

const float PI = std::numbers::pi_v<float>;

Enemy::Enemy(Vector3 emitPos) { 
	Init();
	wt_.translation_ = emitPos;
}

Enemy::~Enemy() {
	delete model_;
	model_ = nullptr;
	delete state_;
	state_ = nullptr;
}

void Enemy::Init() {

	model_ = new Model();
	wt_.Initialize();
	radius_ = 2.0f;
	scale_ = { 1.0f, 1.0f, 1.0f };
	rotate_ = { 0.0f, PI, 0.0f };
	moveVec_ = { 0.0f, 0.0f, -1.0f };
	wt_.translation_ = { 4.0f, 1.5f, 20.0f };
	moveSpeed_ = 0.1f;
	state_ = new EnemyState_Approach(this);
	isAlive_ = true;
	frameCount_ = 0;
	GH_ = TextureManager::Load("symmetryORE_STRONG.jpg");
}

void Enemy::Update() {

	frameCount_++;

	// Stateに応じたアップデート
	state_->Update();

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
}

void Enemy::UpdateBullet() {
}

void Enemy::Rotate() {}

void Enemy::Translate() {
}

void Enemy::Move() {

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ = rotate_;
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	state_ = newState;
}

void Enemy::OnCollision()
{
	isAlive_ = false;
}

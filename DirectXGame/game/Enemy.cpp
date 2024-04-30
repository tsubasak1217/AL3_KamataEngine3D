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
	action_ = APPROACH;
	isAlive_ = true;
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
}

void Enemy::UpdateBullet() {

	switch(action_) {
	case APPROACH:

		// 一定時間ごとに弾を発射
		if(frameCount_ % 60 == 0) {
			gameScenePtr_->AddEnemyBullet(new Bullet(
				wt_.translation_,// 初期座標
				wt_.rotation_,// 初期回転値
				/*-----------------この長いの、プレイヤーの座標----------------*/
				Multiply(
					playerPtr_->GetWorldTransform().translation_,
					RotateMatrix(playerPtr_->GetWorldTransform().parent_->rotation_))
				+ playerPtr_->GetWorldTransform().parent_->translation_
				/*--------------------------------------------------------*/
				- wt_.translation_// プレイヤーの座標から自身の座標を引き、動くベクトルを算出
			));
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

void Enemy::OnCollision()
{
	isAlive_ = false;
}

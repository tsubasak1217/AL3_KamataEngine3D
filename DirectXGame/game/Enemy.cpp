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
	shotInterval_ = 60;
	GH_ = TextureManager::Load("symmetryORE_STRONG.jpg");

	//
	objectType_ = 0b10;
}

void Enemy::Update() {

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
}

void Enemy::Draw() {

	model_->Draw(wt_, *vp_, GH_);
}

void Enemy::AddBullet(){
	// 発射
	Fire();

	// 新しくセット
	std::function<void()>func = std::bind(&Enemy::AddBullet, this);
	timedCalls_.push_back(
		std::make_unique<TimedCall>(func, shotInterval_)
	);
}

void Enemy::UpdateBullet() {
	// 終了した時限発動インスタンスの消去
	std::erase_if(timedCalls_, [](auto& timedCall) { return timedCall->completion_; });
}

void Enemy::Rotate() {}

void Enemy::Translate() {
}

void Enemy::Move() {

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ = rotate_;

	// ワールド行列の作成,転送
	wt_.UpdateMatrix();
	// ワールド座標の更新
	worldPos_ = wt_.translation_;
	// スクリーン座標の更新
	screenPos_ = Multiply({ 0.0f,0.0f,0.0f }, Multiply(wt_.matWorld_, Multiply(vp_->matView,vp_->matProjection)));
	screenPos_ = Multiply(screenPos_, ViewportMatrix({ 1280.0f,720.0f }, {0.0f,0.0f},0.01f,100.0f));
}

void Enemy::Fire(){

	//プレイヤーまでのベクトル
	Vector3 dif = playerPtr_->GetWorldPos() - GetWorldTransform().translation_;

	// ベクトルから発射角を求める
	Vector3 enemyRotate = {
		std::atan2(-dif.y, Length(dif)),// 縦方向の回転角(X軸回り)
		std::atan2(dif.x, dif.z),// 横方向の回転角(Y軸回り)
		0.0f
	};

	// 弾の情報を書き込み作成
	GetGameScenePtr()->AddEnemyBullet(new Bullet(
		wt_.translation_,// 初期座標
		enemyRotate,// 初期回転値
		dif,// 発射ベクトル
		playerPtr_// 追従対象としてプレイヤーのポインタを持たせる
	));
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	state_ = newState;
}

void Enemy::OnCollision()
{
	isAlive_ = false;
}

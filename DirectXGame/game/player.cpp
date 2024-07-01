﻿#include "player.h"
#include "MyFunc.h"
#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
#include "GameScene.h"
#include <ImGui.h>

const float PI = std::numbers::pi_v<float>;

Player::Player() {
	Init();
}

Player::~Player() {
	delete model_;
	model_ = nullptr;
	delete reticleSprite_;
	reticleSprite_ = nullptr;
}

void Player::Init() {

	input_ = Input::GetInstance();
	model_ = new Model();

	wt_.Initialize();
	wt_.translation_ = { 0.0f,0.0f,20.0f };

	// レティクルの初期化
	reticleVec_ = Normalize({ 0.0f,0.0f,1.0f });
	screenReticlePos_ = kWindowSize * 0.5f;
	reticleDistance_ = 60.0f;
	reticleWt_.Initialize();
	reticleWt_.translation_ =
		wt_.translation_ + Multiply(reticleVec_, RotateMatrix(wt_.rotation_)) * reticleDistance_;
	reticleWt_.parent_ = &wt_;
	reticleTexture_ = TextureManager::Load("lockOn.png");
	reticleSprite_ = Sprite::Create(reticleTexture_, { 0.0f,0.0f }, { 0xff,0xff,0xff,0xff }, { 0.5f,0.5f });
	reticleSprite_->SetSize(reticleSprite_->GetSize() * 0.25f);

	//
	radius_ = 2.0f;
	scale_ = { 1.0f, 1.0f, 1.0f };
	rotate_ = { 0.0f, 0.0f, 0.0f };
	moveVec_ = { 0.0f, 0.0f, 0.0f };
	moveSpeed_ = 0.2f;
	GH_ = TextureManager::Load("uvChecker.png");

	shootColltime_ = 0;

	//
	objectType_ = 0b1;
}

void Player::Update() {

	// 弾の発射
	Shoot();

	// 移動量の決定
	Translate();

	// 回転量の決定
	Rotate();

	// 実際に移動
	Move();
}

void Player::Draw() {

	model_->Draw(wt_, *camera_.GetViewProjection(), GH_);
	//model_->Draw(*wt_.parent_, vp, GH_);
}

// レティクルの描画
void Player::DrawReticle()
{

	// レティクルをジョイスティックで移動
	XINPUT_STATE joyState;
	if(Input::GetInstance()->GetJoystickState(0, joyState)){
		screenReticlePos_.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 6.0f;
		screenReticlePos_.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 6.0f;
	}

	// 範囲内に収める
	screenReticlePos_.x = std::clamp(screenReticlePos_.x, 0.0f, kWindowSize.x);
	screenReticlePos_.y = std::clamp(screenReticlePos_.y, 0.0f, kWindowSize.y);

	// 座標を更新して描画
	reticleSprite_->SetPosition(Vector2(screenReticlePos_.x, screenReticlePos_.y));
	reticleSprite_->Draw();
	// 敵のスクリーン座標にレティクルを追従させ,描画
	for(int i = 0; i < lockOnReticles_.size(); i++){
		lockOnReticles_[i]->SetPosition(targets_[i].lock()->GetScreenPos());
		lockOnReticles_[i]->Draw();
	}
}

void Player::Shoot() {

	// 発射クールタイムの更新
	if(shootColltime_ > 0){
		shootColltime_--;
	}

	// 死んでいる敵をターゲットリストから削除
	for(int i = 0; i < targets_.size(); i++){
		if(targets_[i].expired()){
			targets_.erase(targets_.begin() + i);
			lockOnReticles_.erase(lockOnReticles_.begin() + i);
		}
	}

	// ターゲットがいなければロックオンをしない
	if(targets_.size() == 0){ isLockOn_ = false; }

	/*------------------------------------------*/
	//			nearZ,farZ面上のワールド座標を計算
	/*------------------------------------------*/

	// 必要な行列の作成
	Matrix4x4 matVPV = Multiply(vp_->matView, vp_->matProjection);
	matVPV = Multiply(matVPV, ViewportMatrix(kWindowSize, { 0.0f,0.0f, }, 0.0f, 1000.0f));
	Matrix4x4 inverseVPV = InverseMatrix(matVPV);

	Vector3 nearPos = { screenReticlePos_.x,screenReticlePos_.y,0.0f };
	Vector3 farPos = { screenReticlePos_.x,screenReticlePos_.y,1.0f };

	// ワールド座標へ
	nearPos = Transform(nearPos, inverseVPV);
	farPos = Transform(farPos, inverseVPV);

	/*------------------------------------------*/
	//			nearZ → farZ の正規化ベクトルを
	//		　レティクルのワールド座標Z分だけ掛ける
	/*------------------------------------------*/

	Vector3 wpos = Multiply(wt_.translation_, RotateMatrix(wt_.parent_->rotation_)) + wt_.parent_->translation_;
	Vector3 rWPos = nearPos + Normalize(farPos - nearPos) * reticleDistance_;

	/*------------------------------------------*/
	//					発射
	/*------------------------------------------*/
	XINPUT_STATE joyState;

	if(!Input::GetInstance()->GetJoystickState(0, joyState)){ return; }

	if(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
		if(shootColltime_ <= 0) {

			if(!isLockOn_){
				gameScenePtr_->AddPlayerBullet(new Bullet(
					Multiply(wt_.translation_, RotateMatrix(wt_.parent_->rotation_)) + wt_.parent_->translation_,// 初期位置
					wt_.rotation_,// 初期回転量
					Normalize(rWPos - wpos)// 発射ベクトル
				)
				);
			} else{

				for(int i = 0; i < targets_.size(); i++){
					gameScenePtr_->AddPlayerBullet(new Bullet(
						Multiply(wt_.translation_, RotateMatrix(wt_.parent_->rotation_)) + wt_.parent_->translation_,// 初期位置
						wt_.rotation_,// 初期回転量
						Normalize(targets_[i].lock()->GetWorldPos() - worldPos_)// 発射ベクトル
					)
					);
				}
			}

			shootColltime_ = 5;
		}
	}


	ImGui::Begin("iroiro");

	ImGui::DragFloat3("reticlePos", &rWPos.x, 1.0f);
	ImGui::DragFloat3("playerTranslate", &wpos.x, 1.0f);


	ImGui::End();
}

void Player::Rotate() {

	if(input_->PushKey(DIK_A)) {
		rotate_.y -= std::sin((1.0f / 128.0f) * PI);
	}

	if(input_->PushKey(DIK_D)) {
		rotate_.y += std::sin((1.0f / 128.0f) * PI);
	}
}

void Player::Translate() {

	// 移動量の初期化
	moveVec_ = { 0.0f, 0.0f, 0.0f };

	//
	XINPUT_STATE joyState;

	if(Input::GetInstance()->GetJoystickState(0, joyState)){
		moveVec_.x = (float)joyState.Gamepad.sThumbLX / SHRT_MAX * moveSpeed_;
		moveVec_.y = (float)joyState.Gamepad.sThumbLY / SHRT_MAX * moveSpeed_;
	}
}

void Player::Move() {

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_;
	wt_.rotation_ = rotate_;

	// 移動制限
	wt_.translation_.x = std::clamp(wt_.translation_.x, -10.0f, 10.0f);
	wt_.translation_.y = std::clamp(wt_.translation_.y, -6.0f, 6.0f);

	// プレイヤーに合わせてレティクルも移動
	reticleWt_.translation_ = reticleVec_ * reticleDistance_;

	// ワールド行列の作成
	wt_.UpdateMatrix();
	reticleWt_.UpdateMatrix();

	// ワールド座標の更新
	worldPos_ =
		Multiply(wt_.translation_, RotateMatrix(wt_.parent_->rotation_))
		+ wt_.parent_->translation_;
	// スクリーン座標の更新
	screenPos_ = Multiply({ 0.0f,0.0f,0.0f }, Multiply(wt_.matWorld_, Multiply(vp_->matView, vp_->matProjection)));

}

void Player::UpdateReticle()
{

}

void Player::UpdateCamera()
{
	camera_.SetWorldTransform(wt_);
	camera_.UpdateCamera();
}

void Player::OnCollision()
{
}

void Player::LockOn(std::shared_ptr<Enemy> enemy)
{
	isLockOn_ = true;

	for(int i = 0; i < targets_.size(); i++){
		if(targets_[i].lock() == enemy){ return; }
	}

	// 敵をターゲットリストに入れる
	targets_.push_back(enemy);
	// スプライトを敵の座標にpushBack
	lockOnReticles_.push_back(std::make_unique<Sprite>());
	lockOnReticles_.back().reset(
		Sprite::Create(reticleTexture_, enemy->GetScreenPos(), { 0xff,0xff,0xff,0xff }, { 0.5f,0.5f })
	);
	lockOnReticles_.back()->SetSize(lockOnReticles_.back()->GetSize() * 0.2f);
}

#include "player.h"
#include "MyFunc.h"

Player::Player() { Init(); }

Player::~Player() {}

void Player::Init() {
	input_ = Input::GetInstance();

	wt_.Initialize();
	scale_ = {1.0f, 1.0f, 1.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, 0.0f};
	moveSpeed_ = 0.2f;
}

void Player::Update() {

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

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_;
	wt_.rotation_ = rotate_;

	// ワールド行列の作成

	wt_.matWorld_ = AffineMatrix(wt_.scale_, wt_.rotation_, wt_.translation_);
	wt_.TransferMatrix();

}

void Player::Draw() {}

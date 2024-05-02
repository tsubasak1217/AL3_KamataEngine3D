#include "player.h"
#include "MyFunc.h"
#include <algorithm>
#include <cmath>
#include <environment.h>
#include <numbers>
#include "GameScene.h"
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
	reticleDistance_ = 30.0f;
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

	frameCount_ = 0;
}

void Player::Update(const ViewProjection& vp) {

	frameCount_++;

	// 弾の発射
	Shoot(vp);

	// 移動量の決定
	Translate();

	// 回転量の決定
	Rotate();

	// 実際に移動
	Move();

	// ワールド行列の作成
	wt_.UpdateMatrix();
	reticleWt_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& vp) {

	model_->Draw(wt_, vp, GH_);
}

// レティクルの描画
void Player::DrawReticle()
{
	// マウス座標を取得
	POINT mousePos;
	GetCursorPos(&mousePos);
	// マウス座標をウィンドウ左上基準に合わせる
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePos);

	reticleSprite_->SetPosition(Vector2(float(mousePos.x), float(mousePos.y)));

	reticleSprite_->Draw();
}

void Player::Shoot(const ViewProjection& vp) {

	// マウス座標を取得
	POINT mousePos;
	GetCursorPos(&mousePos);
	// マウス座標をウィンドウ左上基準に合わせる
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePos);

	/*------------------------------------------*/
	//			nearZ,farZ面上のワールド座標を計算
	/*------------------------------------------*/

	// 必要な行列の作成
	Matrix4x4 matVPV = Multiply(vp.matView, vp.matProjection);
	matVPV = Multiply(matVPV, ViewportMatrix(kWindowSize, { 0.0f,0.0f, }, 0.0f, 1000.0f));
	Matrix4x4 inverseVPV = InverseMatrix(matVPV);

	Vector3 nearPos = { float(mousePos.x),float(mousePos.y),0.0f };
	Vector3 farPos = { float(mousePos.x),float(mousePos.y),1.0f };

	// ワールド座標へ
	nearPos = Transform(nearPos, inverseVPV);
	farPos = Transform(farPos, inverseVPV);

	/*------------------------------------------*/
	//			nearZ → farZ の正規化ベクトルを
	//		　レティクルのワールド座標Z分だけ掛ける
	/*------------------------------------------*/

	Vector3 reticleWorldPos = Normalize(farPos - nearPos) * (wt_.translation_.z + reticleDistance_);

	/*------------------------------------------*/
	//					発射
	/*------------------------------------------*/

	if(frameCount_ % 5 == 0) {
		gameScenePtr_->AddPlayerBullet(new Bullet(
			Multiply(wt_.translation_, RotateMatrix(wt_.parent_->rotation_)) + wt_.parent_->translation_,// 初期位置
			wt_.rotation_,// 初期回転量
			Normalize(reticleWorldPos - wt_.translation_)// 発射ベクトル
		)
		);
	}
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

	// X軸の移動量決定
	if(input_->PushKey(DIK_LEFT)) {
		moveVec_.x -= moveSpeed_;
	}

	if(input_->PushKey(DIK_RIGHT)) {
		moveVec_.x += moveSpeed_;
	}

	// Y軸の移動量決定
	if(input_->PushKey(DIK_UP)) {
		moveVec_.y += moveSpeed_;
	}

	if(input_->PushKey(DIK_DOWN)) {
		moveVec_.y -= moveSpeed_;
	}
}

void Player::Move() {

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_;
	wt_.rotation_ = rotate_;

	// 移動制限
	wt_.translation_.x = std::clamp(wt_.translation_.x, -33.0f, 33.0f);
	wt_.translation_.y = std::clamp(wt_.translation_.y, -18.0f, 18.0f);

	// プレイヤーに合わせてレティクルも移動
	reticleWt_.translation_ = reticleVec_ * reticleDistance_;
}

void Player::UpdateReticle()
{

}

void Player::OnCollision()
{
}

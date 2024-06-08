#include "Bullet.h"
#include "MyFunc.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const Vector3& pos, const Vector3& rotate, const Vector3& moveVec, Object* homingObjectPtr) {
	Init();
	wt_.Initialize();
	wt_.translation_ = pos;
	wt_.rotation_ = rotate;
	moveVec_ = Normalize(moveVec);
	homingObjectPtr_ = homingObjectPtr;
	homingLevel_ = 0.1f;
}

Bullet::~Bullet() { Fin(); }

void Bullet::Init() {
	model_ = Model::Create();
	radius_ = 2.0f;
	scale_ = {0.5f, 0.5f, 3.0f};
	rotate_ = {0.0f, 0.0f, 0.0f};
	moveVec_ = {0.0f, 0.0f, 1.0f};
	GH_ = TextureManager::Load("uvChecker.png");
	deathTimer_ = kLifetime_;
	moveSpeed_ = 1.0f;
}

void Bullet::Update() {

	// 寿命
	deathTimer_--;

	// ホーミングさせる
	Homing();

	prePos_ = wt_.translation_;

	// 移動ベクトルの加算
	wt_.scale_ = scale_;
	wt_.translation_ += moveVec_ * moveSpeed_;
	wt_.rotation_ += rotate_;

	if(std::abs(Length(wt_.translation_) - Length(prePos_)) > 1.0f){
		moveVec_ = moveVec_;
	}

	// ワールド座標の更新
	worldPos_ = wt_.translation_;

	// ワールド行列の作成
	wt_.UpdateMatrix();
}

void Bullet::Draw(const ViewProjection& vp) { model_->Draw(wt_, vp, GH_); }

void Bullet::Fin() {
	delete model_;
	model_ = nullptr;
}

void Bullet::Homing(){

	// ホーミング対象がなければ処理しない
	if(!homingObjectPtr_){ return; }

	// 座標を取得
	Vector3 aimPos = homingObjectPtr_->GetWorldPos();
	// 差分ベクトルを正規化
	Vector3 dif = Normalize(aimPos - wt_.translation_);
	// ホーミングさせる
	moveVec_ = Slerp(moveVec_, dif, homingLevel_);

	// 移動ベクトルから回転角をを求め更新する
	wt_.rotation_ = {
		std::atan2(-moveVec_.y, Length(moveVec_)),// 縦方向の回転角(X軸回り)
		std::atan2(moveVec_.x, moveVec_.z),// 横方向の回転角(Y軸回り)
		0.0f
	};
}

void Bullet::OnCollision(){
	deathTimer_ = 0;
}

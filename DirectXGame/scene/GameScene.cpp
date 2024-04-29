#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include "MyFunc.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	sprite_ = nullptr;
	delete dc_;
	dc_ = nullptr;
	railCamera_.reset();
	delete enemy_;
	enemy_ = nullptr;
	delete player_;
	player_ = nullptr;
	skydome_.reset();
}

void GameScene::Initialize() {

	// レールカメラ
	railCamera_.reset(new RailCamera({0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f}));
	// プレイヤー
	player_ = new Player();
	player_->SetParentPtr(railCamera_->GetWorldTransform());// レールカメラに追従するよう親子関係を持たせる
	// 敵
	enemy_ = new Enemy();
	enemy_->SetPlayerPtr(player_);
	// 天球
	skydome_.reset(new Skydome());

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	sprite_ = Sprite::Create(textureHandle_, Vector2(100, 50));
	player_->SetModel(Model::Create());
	enemy_->SetModel(Model::Create());

	// デバックカメラ
	dc_ = new DebugCamera(1280, 720);
	isDebugCameraActive_ = false;


	wt_.Initialize();

	AxisIndicator::SetVisible(true);
	AxisIndicator::SetTargetViewProjection(railCamera_->GetViewProjection());
}

void GameScene::Update() {

	// カメラの更新
	railCamera_->Update();

	// オブジェクトの更新
	player_->Update();
	enemy_->Update();
	skydome_->Update();

	CheckCollision();

	// デバッグテキストの出力----------------------------------
#ifdef _DEBUG

	// ENTERでデバッグカメラの有効化
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ != true ? isDebugCameraActive_ = true : isDebugCameraActive_ = false;
	}

	// デバッグカメラが有効かどうかでvpを変更する
	if (isDebugCameraActive_) {
		dc_->Update();
		railCamera_->GetViewProjection()->matProjection = dc_->GetViewProjection().matProjection;
		railCamera_->GetViewProjection()->matView = dc_->GetViewProjection().matView;
		railCamera_->GetViewProjection()->TransferMatrix();

	} else {
		//railCamera_->GetViewProjection()->UpdateMatrix();
	}

	ImGui::Begin("Enemy");
	ImGui::InputFloat3("enemyPos", &enemy_->GetWorldTransform().translation_.x);
	ImGui::SliderFloat3("enemyPos", &enemy_->GetWorldTransform().translation_.x, 0.0f, 1.0f);
	ImGui::Checkbox("isDebugCameraActive(key [ENTER] to change)", &isDebugCameraActive_);
	ImGui::End();

#endif // DEBUG
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	skydome_->Draw(*railCamera_->GetViewProjection());// モデルの描画
	player_->Draw(*railCamera_->GetViewProjection());
	enemy_->Draw(*railCamera_->GetViewProjection());

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	///

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckCollision(){

	Vector3 playerPos =
		Multiply(
			player_->GetWorldTransform().translation_,
			RotateMatrix(player_->GetWorldTransform().parent_->rotation_))
		+ player_->GetWorldTransform().parent_->translation_;

	// 敵弾と自分
	for(auto& bullet : enemy_->GetBullets()){
		float distance = Length(
			playerPos - bullet->GetWorldTransform().translation_
		);

		if(distance <= player_->GetRadius() + bullet->GetRadius()){
			player_->OnCollision();
			bullet->OnCollision();
		}
	}

	// 自弾と敵
	for(auto& bullet : player_->GetBullets()){
		float distance = Length(
			enemy_->GetWorldTransform().translation_ -
			bullet->GetWorldTransform().translation_
		);

		if(distance <= enemy_->GetRadius() + bullet->GetRadius()){
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}

	// 自弾と敵弾
	for(auto& playerBullet : player_->GetBullets()){
		for(auto& enemyBullet : enemy_->GetBullets()){
			float distance = Length(
				playerBullet->GetWorldTransform().translation_ -
				enemyBullet->GetWorldTransform().translation_
			);

			if(distance <= playerBullet->GetRadius() + enemyBullet->GetRadius()){
				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}
	}
}

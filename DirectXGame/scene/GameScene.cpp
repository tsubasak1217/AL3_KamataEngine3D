#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete dc_;
	delete player_;
}

void GameScene::Initialize() {

	player_ = new Player();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	sprite_ = Sprite::Create(textureHandle_, Vector2(100, 50));
	player_->SetModel(Model::Create());

	// デバックカメラ
	dc_ = new DebugCamera(1280, 720);
	isDebugCameraActive_ = false;

	wt_.Initialize();
	vp_.Initialize();

	AxisIndicator::SetVisible(true);
	AxisIndicator::SetTargetViewProjection(&vp_);
}

void GameScene::Update() {

	player_->Update();

	// デバッグテキストの出力----------------------------------
#ifdef _DEBUG

	// SPACEでデバッグカメラの有効化
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ != true ? isDebugCameraActive_ = true : isDebugCameraActive_ = false;
	}

	// デバッグカメラが有効かどうかでvpを変更する
	if (isDebugCameraActive_) {
		dc_->Update();
		vp_.matProjection = dc_->GetViewProjection().matProjection;
		vp_.matView = dc_->GetViewProjection().matView;
		vp_.TransferMatrix();

	} else {
		vp_.UpdateMatrix();
	}

	ImGui::Begin("Player");
	ImGui::InputFloat3("playerPos", &player_->GetWorldTransform().translation_.x);
	ImGui::SliderFloat3("playerPoss", &player_->GetWorldTransform().translation_.x, 0.0f, 1.0f);
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
	player_->Draw(vp_); // モデルの描画

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

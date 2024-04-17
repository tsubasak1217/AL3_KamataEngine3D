#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_;
	delete player_;
}

void GameScene::Initialize() {

	player_ = new Player;

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	player_->SetModel(Model::Create());

	wt_.Initialize();
	vp_.Initialize();
}


void GameScene::Update() {

	player_->Update();

	// デバッグテキストの出力----------------------------------
#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::InputFloat3("playerPos", &player_->GetWorldTransform().translation_.x);
	ImGui::SliderFloat3("playerPoss", &player_->GetWorldTransform().translation_.x, 0.0f, 1.0f);
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
	player_->GetModel()->Draw(player_->GetWorldTransform(), vp_, textureHandle_); // モデルの描画

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

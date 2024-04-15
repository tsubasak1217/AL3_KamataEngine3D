#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();

	wt_.Initialize();
	vp_.Initialize();

	// サウンド
	soundHandle_ = audio_->LoadWave("fanfare.wav");
	audio_->PlayWave(soundHandle_,true);

	// デバックカメラ
	dc_ = new DebugCamera(1280,720);

	// ライン
	PrimitiveDrawer::GetInstance()->SetViewProjection(&dc_->GetViewProjection());

	// 軸表示有効化
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&dc_->GetViewProjection());
}

void GameScene::Update() {

	// スプライトの移動---------------------------------------
	Vector2 spritePos_ = sprite_->GetPosition();
	spritePos_ += {2.0f, 1.0f};
	sprite_->SetPosition(spritePos_);

	//音声の停止---------------------------------------------
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(soundHandle_);
	}

	// デバッグテキストの出力----------------------------------
#ifdef _DEBUG
	ImGui::Begin("Debug1");
	//ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3", inputFloat);
	ImGui::SliderFloat3("SliderFloat3", inputFloat,0.0f,1.0f);
	ImGui::ShowDemoWindow();
	ImGui::End();
#endif // DEBUG

	// デバックカメラ
	dc_->Update();
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
	model_->Draw(wt_, dc_->GetViewProjection(), textureHandle_); // モデルの描画
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});// ラインの描画

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	///
	
	sprite_->Draw(); // スプライトの描画---------------------

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

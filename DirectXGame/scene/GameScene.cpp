#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>
#include "MyFunc.h"
#include "player.h"
#include "Enemy.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	sprite_ = nullptr;
	delete dc_;
	dc_ = nullptr;
	railCamera_.reset();
	for(auto& enemy : enemy_){ enemy.reset(); }
	delete player_;
	player_ = nullptr;
	for(auto& bullet : enemyBullets_){ bullet.reset(); }
	for(auto& bullet : playerBullets_){ bullet.reset(); }
	skydome_.reset();
}

void GameScene::Initialize() {

	// レールカメラ
	railCamera_.reset(new RailCamera({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }));
	// プレイヤー
	player_ = new Player();
	player_->SetParentPtr(railCamera_->GetWorldTransform());// レールカメラに追従するよう親子関係を持たせる
	player_->SetGameScenePtr(this);// ゲームシーンのポインタを持たせる
	player_->SetCameraPtr(railCamera_.get());

	// 天球
	skydome_.reset(new Skydome());

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

	// 敵の行動コマンド
	LoadEnemyCommands("Resources/enemyAction.csv");
	isWait_ = false;
	waitTimer_ = 0;
	
	//
	wt_.Initialize();

	// レティクルのテクスチャを先に読み込む
	TextureManager::Load("lockOn.png");

	//
	AxisIndicator::SetVisible(true);
	AxisIndicator::SetTargetViewProjection(railCamera_->GetViewProjection());
}

void GameScene::Update() {

	// 一定時間経過した弾の削除
	std::erase_if(enemyBullets_, [](auto& bullet) { return !(bullet->GetIsAlive()); });
	std::erase_if(playerBullets_, [](auto& bullet) { return !(bullet->GetIsAlive()); });
	// 死んでいる敵の削除
	std::erase_if(enemy_, [](auto& enemy) { return !(enemy->GetIsAlive()); });

	// カメラの更新
	railCamera_->Update();

	// 敵の行動決定
	if(!isWait_){
		UpdateEnemyCommands();
	} else{
		waitTimer_--;
		waitTimer_ <= 0 ? isWait_ = false : isWait_;
	}

	// オブジェクトの更新
	player_->Update(*railCamera_->GetViewProjection());
	for(auto& enemy : enemy_){ enemy->Update(); }
	skydome_->Update();

	// 弾の更新
	for(auto& bullet : enemyBullets_) { bullet->Update(); }
	for(auto& bullet : playerBullets_) { bullet->Update(); }

	CheckCollision();

	// デバッグテキストの出力----------------------------------
#ifdef _DEBUG

	// ENTERでデバッグカメラの有効化
	if(input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ != true ? isDebugCameraActive_ = true : isDebugCameraActive_ = false;
	}

	// デバッグカメラが有効かどうかでvpを変更する
	if(isDebugCameraActive_) {
		dc_->Update();
		railCamera_->GetViewProjection()->matProjection = dc_->GetViewProjection().matProjection;
		railCamera_->GetViewProjection()->matView = dc_->GetViewProjection().matView;
		railCamera_->GetViewProjection()->TransferMatrix();

	} else {
		//railCamera_->GetViewProjection()->UpdateMatrix();
	}

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
	for(auto& enemy : enemy_){ enemy->Draw(*railCamera_->GetViewProjection()); }
	for(auto& bullet : enemyBullets_) {
		bullet->Draw(*railCamera_->GetViewProjection());
	}
	for(auto& bullet : playerBullets_) {
		bullet->Draw(*railCamera_->GetViewProjection());
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	///

	player_->DrawReticle();

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// オブジェクト同士の当たり判定を取る関数
void GameScene::CheckCollisionPair(Object* obj1, Object* obj2){

	float distance = Length(obj1->GetWorldPos() - obj2->GetWorldPos());

	if(distance <= obj1->GetRadius() + obj2->GetRadius()){
		obj1->OnCollision();
		obj2->OnCollision();
	}
}

void GameScene::CheckCollision(){

	// 敵弾と自分
	for(auto& bullet : enemyBullets_){
		CheckCollisionPair(bullet.get(), player_);
	}

	// 自弾と敵
	for(auto& bullet : playerBullets_){
		for(auto& enemy : enemy_){
			CheckCollisionPair(bullet.get(), enemy.get());
		}
	}

	// 自弾と敵弾
	for(auto& playerBullet : playerBullets_){
		for(auto& enemyBullet : enemyBullets_){
			CheckCollisionPair(enemyBullet.get(), playerBullet.get());
		}
	}
}

void GameScene::UpdateEnemyCommands()
{
	// 行の文字列を格納する変数
	std::string line;

	while(getline(enemyCommands_, line)){

		std::istringstream line_stream(line);
		std::string word;

		// カンマ区切りでwordに先頭文字列を格納
		getline(line_stream, word, ',');

		// コメントアウトの行を飛ばす
		if(word.find("//") == 0){
			continue;
		}

		// 待機命令を受け取る
		if(word.find("WAIT") == 0){

			// 待機時間を格納する
			getline(line_stream, word, ',');
			int32_t waitTime = std::atoi(word.c_str());

			// 敵の待機フラグを立て、タイマーを設定
			waitTimer_ = waitTime;
			isWait_ = true;

			break;
		}

		// 敵を出現させる
		if(word.find("POP") == 0){

			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			Vector3 emitPos(x, y, z);

			// 敵の出現
			enemy_.push_back(std::make_unique<Enemy>(emitPos));
			enemy_.back()->SetPlayerPtr(player_);
			enemy_.back()->SetGameScenePtr(this);// ゲームシーンのポインタを持たせる
			enemy_.back()->SetModel(Model::Create());
		}
	}
}


void GameScene::LoadEnemyCommands(std::string filePath)
{
	// ファイルを開く
	std::fstream file;
	file.open(filePath);
	assert(file.is_open());

	// ファイルの中身をコピー
	enemyCommands_ << file.rdbuf();

	// ファイル閉じる
	file.close();
}

void GameScene::AddEnemyBullet(Bullet* bullet)
{
	enemyBullets_.push_back(std::make_unique<Bullet>());
	enemyBullets_.back().reset(bullet);
}

void GameScene::AddPlayerBullet(Bullet* bullet)
{
	playerBullets_.push_back(std::make_unique<Bullet>());
	playerBullets_.back().reset(bullet);
}

#pragma once
#include <sstream>
#include "Audio.h"
#include "AxisIndicator.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "skydome.h"
#include "railCamera.h"
#include "Bullet.h"

class Player;
class Enemy;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// 天球
	std::unique_ptr<Skydome>skydome_;

	// プレイヤー
	Player* player_ = nullptr;

	// 敵
	std::list<std::unique_ptr<Enemy>> enemy_;

	// 弾
	std::list<std::unique_ptr<Bullet>> enemyBullets_;
	std::list<std::unique_ptr<Bullet>> playerBullets_;

	// カメラ
	DebugCamera* dc_ = nullptr;
	std::unique_ptr<RailCamera> railCamera_;
	bool isDebugCameraActive_;

	// 3d描画のための変数
	WorldTransform wt_;
	//ViewProjection vp_;

	// テクスチャ
	uint32_t textureHandle_;
	Sprite* sprite_ = nullptr;

	// imgui
	float inputFloat[3] = {0.0f, 0.0f, 0.0f};

	// 敵の行動コマンド
	std::stringstream enemyCommands_;
	bool isWait_;
	int32_t waitTimer_;

private:
	void CheckCollisionPair(Object* obj1,Object* obj2);
	void CheckCollision();
	void LoadEnemyCommands(std::string filePath);
	void UpdateEnemyCommands();

public:
	void AddEnemyBullet(Bullet* bullet);
	void AddPlayerBullet(Bullet* bullet);

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

#pragma once

#include "Audio.h"
#include "AxisIndicator.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "player.h"

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

	// プレイヤー
	Player* player_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;

	// デバックカメラ
	DebugCamera* dc_ = nullptr;
	bool isDebugCameraActive_;

	// 3d描画のための変数
	WorldTransform wt_;
	ViewProjection vp_;

	// テクスチャ
	uint32_t textureHandle_;
	Sprite* sprite_ = nullptr;

	// imgui
	float inputFloat[3] = {0.0f, 0.0f, 0.0f};

private:
	void CheckCollision();

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

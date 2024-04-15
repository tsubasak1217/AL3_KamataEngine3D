#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"

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
	Model* model_ = nullptr;

	//デバックカメラ
	DebugCamera* dc_ = nullptr;

	// 3d描画のための変数
	WorldTransform wt_;
	ViewProjection vp_;

	// テクスチャ
	uint32_t textureHandle_;
	Sprite* sprite_ = nullptr;

	// サウンド
	uint32_t soundHandle_ = 0;

	// imgui
	float inputFloat[3] = {0.0f, 0.0f, 0.0f};


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

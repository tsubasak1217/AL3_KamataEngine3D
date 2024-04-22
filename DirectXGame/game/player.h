#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"

class Player {

public:
	// コンストラクタ.デストラクタ
	Player();
	~Player();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw();

private:

	// 入力
	Input* input_ = nullptr;

	// 半径
	float radius_ = 64.0f;
	// 拡縮・回転・移動に関する変数
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 moveVec_;
	float moveSpeed_;

	// ワールド変換データ
	WorldTransform wt_;

	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t GH_ = 0u;

public:

	Model* GetModel() { return model_; }
	void SetModel(Model* model) { model_ = model; }

	WorldTransform& GetWorldTransform() { return wt_; }
};
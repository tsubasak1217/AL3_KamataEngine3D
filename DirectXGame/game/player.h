#include "Model.h"
#include "WorldTransform.h"

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
	// ワールド変換データ
	WorldTransform wt_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t GH_ = 0u;

public:

	Model* GetModel() { return model_; }
	void SetModel(Model* model) { model_ = model; }

};
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Object.h"
#include "Bullet.h"
#include "railCamera.h"

class GameScene;

class Player : public Object {

public:
	// コンストラクタ.デストラクタ
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;

private:

	Input* input_ = nullptr;
	GameScene* gameScenePtr_;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Translate();
	void Move();

public:
	void OnCollision();
	void SetGameScenePtr(GameScene* gameScenePtr){ gameScenePtr_ = gameScenePtr; }
};
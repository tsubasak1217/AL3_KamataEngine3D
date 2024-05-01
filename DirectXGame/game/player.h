#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Object.h"
#include "Bullet.h"
#include "railCamera.h"
#include "sprite.h"

class GameScene;

class Player : public Object {

public:
	// コンストラクタ.デストラクタ
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;
	void DrawReticle(const ViewProjection& vp);

private:

	Input* input_ = nullptr;
	GameScene* gameScenePtr_;
	
	WorldTransform reticleWt_;
	Vector3 reticleVec_;
	float reticleDistance_;
	uint32_t reticleTexture_;
	Sprite* reticleSprite_ = nullptr;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Translate();
	void Move();
	void UpdateReticle();

public:
	void OnCollision();
	void SetGameScenePtr(GameScene* gameScenePtr){ gameScenePtr_ = gameScenePtr; }
};
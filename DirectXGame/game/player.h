#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Object.h"
#include "Bullet.h"
#include "railCamera.h"
#include "sprite.h"
#include <memory>

class Enemy;
class GameScene;

class Player : public Object {

public:
	// コンストラクタ.デストラクタ
	Player();
	~Player();

	void Init() override;
	void Update();
	void Draw() override;
	void DrawReticle();

private:

	Input* input_ = nullptr;
	GameScene* gameScenePtr_;
	
	WorldTransform reticleWt_;
	Vector3 reticleVec_;
	Vector2 screenReticlePos_;
	float reticleDistance_;
	uint32_t reticleTexture_;
	Sprite* reticleSprite_ = nullptr;
	bool isLockOn_ = false;
	std::vector<std::weak_ptr<Enemy>>targets_;

	uint32_t shootColltime_;

	RailCamera* railcamera_ = nullptr;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Translate();
	void Move();
	void UpdateReticle();

public:
	void SetGameScenePtr(GameScene* gameScenePtr){ gameScenePtr_ = gameScenePtr; }
	void SetCameraPtr(RailCamera* railcamera){ railcamera_ = railcamera; }
	Vector2 GetReticlePos(){ return screenReticlePos_; }

public:
	void OnCollision()override;
	void SetIsLockOn(bool flag){ isLockOn_ = flag; }
	void LockOn(std::shared_ptr<Enemy> enemy);
};
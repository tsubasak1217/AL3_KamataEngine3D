#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GameScene;
class Player;

enum ACTION {
	APPROACH,
	EXIT
};

class Enemy : public Object {

public:
	// コンストラクタ.デストラクタ
	Enemy(Vector3 emitPos);
	~Enemy();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;

private:
	Player* playerPtr_ = nullptr;
	GameScene* gameScenePtr_ = nullptr;
	int action_;
	int frameCount_;
	bool isAlive_;

private: // メンバ関数
	void UpdateBullet();
	void Rotate();
	void Translate();
	void Move();

public:
	void OnCollision();

public:
	void SetPlayerPtr(Player* playerPtr) { playerPtr_ = playerPtr; }
	void SetGameScenePtr(GameScene* gameScenePtr) { gameScenePtr_ = gameScenePtr; }
	WorldTransform& GetWorldTransform() { return wt_; }

	void SetIsAlive(bool flag){ isAlive_ = flag; }
	bool GetIsAlive()const{ return isAlive_; }
};
#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "EnemyState.h"

class GameScene;
class Player;

enum class ACTION {
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
	size_t action_;
	int frameCount_;
	bool isAlive_;

private:
	BaseEnemyState* state_;

private: // メンバ関数
	void UpdateBullet();
	void Rotate();
	void Translate();
	void Move();

	/*void Approach();
	void Exit();*/

	//static void (Enemy::*pActionFunc[])();

public:
	void ChangeState(BaseEnemyState* newState);
	void OnCollision();

public:// アクセッサ
	void SetPlayerPtr(Player* playerPtr) { playerPtr_ = playerPtr; }
	Player* GetPlayerPtr()const{ return playerPtr_; }

	void SetGameScenePtr(GameScene* gameScenePtr) { gameScenePtr_ = gameScenePtr; }
	GameScene* GetGameScenePtr()const{ return gameScenePtr_; }

	void SetIsAlive(bool flag){ isAlive_ = flag; }
	bool GetIsAlive()const{ return isAlive_; }

	int GetFrameCount()const{ return frameCount_; }

	void SetMoveVec(const Vector3& moveVec){ moveVec_ = moveVec; }
};
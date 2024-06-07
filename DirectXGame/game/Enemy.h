#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "EnemyState.h"
#include "TimedCall.h"
#include <functional>
#include <list>
#include <memory>

class GameScene;
class Player;

class Enemy : public Object {

	// 各ステートをfriend classに設定してアクセス権をあげる
	friend class BaseEnemyState;
	friend class EnemyState_Approach;
	friend class EnemyState_Exit;

public:
	// コンストラクタ.デストラクタ
	Enemy(Vector3 emitPos);
	~Enemy();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;

private:// 外部参照のためのポインタ変数
	Player* playerPtr_ = nullptr;
	GameScene* gameScenePtr_ = nullptr;

private:// 通常のメンバ変数
	uint32_t shotInterval_;
	bool isAlive_;

private:// メンバ変数(クラス)
	BaseEnemyState* state_;
	std::list<std::unique_ptr<TimedCall>>timedCalls_;

private: // プライベートメンバ関数
	void UpdateBullet();
	void Rotate();
	void Translate();
	void Move();
	void Fire();

public:// 誰からもアクセス可能
	void OnCollision();

private:// ステートクラスが操作する関数
	void ChangeState(BaseEnemyState* newState);
	void AddBullet();

public:// アクセッサ
	void SetPlayerPtr(Player* playerPtr) { playerPtr_ = playerPtr; }

	void SetGameScenePtr(GameScene* gameScenePtr) { gameScenePtr_ = gameScenePtr; }
	GameScene* GetGameScenePtr()const{ return gameScenePtr_; }

	void SetIsAlive(bool flag){ isAlive_ = flag; }
	bool GetIsAlive()const{ return isAlive_; }

	void SetMoveVec(const Vector3& moveVec){ moveVec_ = moveVec; }
};
#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

enum class ACTION {
	APPROACH,
	EXIT
};

class Enemy : public Object {

public:
	// コンストラクタ.デストラクタ
	Enemy();
	~Enemy();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;

private:
	std::list<std::unique_ptr<Bullet>> bullets_;
	Player* playerPtr_ = nullptr;
	size_t action_;
	int frameCount_;
	float velocity_;

private: // メンバ関数
	void UpdateBullet();
	void Rotate();
	void Translate();
	void Move();

	// アクションごとの関数
	void Approach();
	void Exit();

	// メンバ関数テーブル
	static void (Enemy::*pMenberFunc[])();

public:
	void SetPlayerPtr(Player* playerPtr) { playerPtr_ = playerPtr; }
	WorldTransform& GetWorldTransform() { return wt_; }
};
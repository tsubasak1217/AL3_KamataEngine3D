#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

enum ACTION {
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
	int action_;
	int frameCount_;

private: // メンバ関数
	void UpdateBullet();
	void Rotate();
	void Translate();
	void Move();

public:
	void SetPlayerPtr(Player* playerPtr) { playerPtr_ = playerPtr; }
	WorldTransform& GetWorldTransform() { return wt_; }
};
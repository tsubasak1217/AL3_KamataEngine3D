#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Object.h"
#include "Bullet.h"

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
	std::list<std::unique_ptr<Bullet>> bullets_;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Translate();
	void Move();

public:
};
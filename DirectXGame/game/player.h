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
	std::vector<Bullet*> bullets_;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Move();

public:
	Model* GetModel() { return model_; }
	void SetModel(Model* model) { model_ = model; }

	WorldTransform& GetWorldTransform() { return wt_; }
};
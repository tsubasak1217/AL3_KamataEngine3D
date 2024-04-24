#include "Bullet.h"
#include "Input.h"
#include "Model.h"
#include "Object.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy : public Object {

public:
	// コンストラクタ.デストラクタ
	Enemy();
	~Enemy();

	void Init() override;
	void Update() override;
	void Draw(const ViewProjection& vp) override;

private:
	std::list<Bullet*> bullets_;

private: // メンバ関数
	void Shoot();
	void Rotate();
	void Translate();
	void Move();

public:
	Model* GetModel() { return model_; }
	void SetModel(Model* model) { model_ = model; }

	WorldTransform& GetWorldTransform() { return wt_; }
};
#include "EnemyState.h"
#include "Enemy.h"
#include "player.h"
#include "GameScene.h"
#include "MyFunc.h"

void BaseEnemyState::ShiftState(BaseEnemyState* nextState){

	pEnemy_->ChangeState(nextState);
}


/* ----------------------------- APPROACH -------------------------------- */

EnemyState_Approach::EnemyState_Approach(Enemy* pEnemy) : BaseEnemyState("Approach", pEnemy){
	// 最初の一発をセット
	std::function<void()>func = std::bind(&Enemy::AddBullet, pEnemy_);
	pEnemy_->timedCalls_.push_back(
		std::make_unique<TimedCall>(func, pEnemy->shotInterval_)
	);
}

EnemyState_Approach::~EnemyState_Approach(){
}

void EnemyState_Approach::Update()
{
	// 一定時間ごとに弾を発射
	for(auto& timedCall : pEnemy_->timedCalls_){
		timedCall->Update();
	}
	
	// 条件を満たしたら動くベクトルを変更し状態遷移
	if(pEnemy_->GetWorldTransform().translation_.z < 0.0f){
		pEnemy_->SetMoveVec({ -1.0f,1.0f,0.0f });
		pEnemy_->ChangeState(new EnemyState_Exit(pEnemy_));
	}
}

/* ------------------------------- EXIT ---------------------------------- */

EnemyState_Exit::EnemyState_Exit(Enemy* pEnemy) : BaseEnemyState("Exit", pEnemy){}

EnemyState_Exit::~EnemyState_Exit()
{
}

void EnemyState_Exit::Update()
{
}

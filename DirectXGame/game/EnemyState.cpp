#include "EnemyState.h"
#include "Enemy.h"
#include "player.h"
#include "GameScene.h"
#include "MyFunc.h"

void BaseEnemyState::ShiftState(BaseEnemyState* nextState)
{
	pEnemy_->ChangeState(nextState);
}


/* ----------------------------- APPROACH -------------------------------- */

EnemyState_Approach::EnemyState_Approach(Enemy* pEnemy) : BaseEnemyState("Approach", pEnemy){}

EnemyState_Approach::~EnemyState_Approach()
{
}

void EnemyState_Approach::Update()
{
	// 一定時間ごとに弾を発射
	if(pEnemy_->GetFrameCount() % 60 == 0) {
		pEnemy_->GetGameScenePtr()->AddEnemyBullet(new Bullet(
			pEnemy_->GetWorldTransform().translation_,// 初期座標
			pEnemy_->GetWorldTransform().rotation_,// 初期回転値
			/*-----------------この長いの、プレイヤーの座標----------------*/
			Multiply(
				pEnemy_->GetPlayerPtr()->GetWorldTransform().translation_,
				RotateMatrix(pEnemy_->GetPlayerPtr()->GetWorldTransform().parent_->rotation_))
			+ pEnemy_->GetPlayerPtr()->GetWorldTransform().parent_->translation_
			/*--------------------------------------------------------*/
			- pEnemy_->GetWorldTransform().translation_// プレイヤーの座標から自身の座標を引き、動くベクトルを算出
		));
	}
	
	if(pEnemy_->GetWorldTransform().translation_.z < 0.0f){
		pEnemy_->SetMoveVec({ -1.0f,1.0f,0.0f });
		pEnemy_->ChangeState(new EnemyState_Exit(pEnemy_));
	}
}

/* ------------------------------- EXIT ---------------------------------- */

EnemyState_Exit::EnemyState_Exit(Enemy* pEnemy) : BaseEnemyState("Approach", pEnemy){}

EnemyState_Exit::~EnemyState_Exit()
{
}

void EnemyState_Exit::Update()
{
}

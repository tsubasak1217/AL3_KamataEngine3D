#include "CollisionManager.h"
#include "MyFunc.h"
#include "Enemy.h"
#include "Player.h"

void CollisionManager::CheckCollisionPair(Object* obj1, Object* obj2){


	float distance = Length(obj1->GetWorldPos() - obj2->GetWorldPos());

	if(distance <= obj1->GetRadius() + obj2->GetRadius()){

		// 違う属性のときのみ
		if((obj1->objectType_ & obj2->objectType_) != obj1->objectType_){
			obj1->OnCollision();
			obj2->OnCollision();
		}
	}
}

void CollisionManager::CheckReticleCollision()
{
	// レティクルと敵の距離を測りロックオン処理
	pPlayer_->SetIsLockOn(false);
	for(auto& enemy : *pEnemy_){
		float distance = Length(enemy->GetScreenPos() - pPlayer_->GetReticlePos());

		if(distance < 50.0f){
			pPlayer_->LockOn(enemy);
		}
	}
}

void CollisionManager::PushBackCollider(Object* collider){
	colliders_.push_back(collider);
}

void CollisionManager::CheckCollision(){

	// 対象が1以下のときは判定を取らない
	if(colliders_.size() <= 1){ return; }
	
	CheckReticleCollision();

	// 総当たりで当たり判定
	std::list<Object*>::iterator itrA = colliders_.begin();
	for(; itrA != colliders_.end(); ++itrA){
		std::list<Object*>::iterator itrB = itrA;
		itrB++;
		for(; itrB != colliders_.end(); ++itrB){
			CheckCollisionPair(*itrA, *itrB);
		}
	}

}

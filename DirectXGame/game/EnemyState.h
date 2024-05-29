#pragma once
#include "string"

class Enemy;

class BaseEnemyState{
public:
	BaseEnemyState(const std::string& name, Enemy* pEnemy) : name_(name), pEnemy_(pEnemy){};
	virtual ~BaseEnemyState(){};
	void ShiftState(BaseEnemyState* nextState);
	virtual void Update() = 0;

protected:
	std::string name_;
	Enemy* pEnemy_;
};

class EnemyState_Approach : public BaseEnemyState{
public:
	EnemyState_Approach(Enemy* pEnemy);
	~EnemyState_Approach();
	void Update()override;
};

class EnemyState_Exit : public BaseEnemyState{
public:
	EnemyState_Exit(Enemy* pEnemy);
	~EnemyState_Exit();
	void Update()override;
};
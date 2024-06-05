#include "TimedCall.h"

// コンストラクタで関数ポインタとタイマーをセット
TimedCall::TimedCall(const std::function<void()>& function, uint32_t timer)
	: CallBack(function), timer_(timer){};

void TimedCall::Update(){

	// 完了していた場合実行しない
	if(completion_){ return; }

	if(timer_ <= 0){
		// タイマーが0になると実行
		CallBack();
		completion_ = true;
		return;

	} else{
		// 実行までタイマーをカウントダウン
		timer_--;
	}
};

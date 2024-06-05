#pragma once
#include <functional>
#include <stdint.h>


class TimedCall{

public:// 基本的な関数
	TimedCall() = default;
	TimedCall(const std::function<void()>& function, uint32_t timer);
	~TimedCall(){};
	void Update();

public:// 完了フラグ
	bool completion_ = false;

private:// 関数ポインタと呼び出すまでのタイマー
	std::function<void()> CallBack;
	uint32_t timer_;

};
#pragma once

#include <iostream>
#include <queue>
#include <chrono>
#include <string>
#include <mutex>
#include <thread>
#include <functional>

/*事件队列模式
* 解耦生产者 - 消费者
* 平衡不同处理速度
* 顺序处理
* 并发安全
* 
* 优点:
* 1.异步处理
* 2.解耦模块
* 3.FIFO顺序
* 4.安全传递数据
* 
* 缺点:
* 1.有延迟
* 2.需要额外内存管理
* 
* 适用场景:
* 游戏引擎的消息系统
* 鼠标, 键盘, 手柄输入事件, GUI事件
* 碰撞事件
* 网络数据包事件
* 
* UE:
* 输入事件, 网络消息处理 UNetDriver 线程队列, 异步任务
*/

struct Event
{
	int id;
	std::string payload;
};

class EventQueue
{
public:
	void Push(const Event& e)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push(e);
	}

	bool Pop(Event& e)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		
		if (queue_.empty()) return false;
		
		e = queue_.front();
		queue_.pop();
		return true;
	}
private:
	std::queue<Event> queue_;
	std::mutex mutex_;
};

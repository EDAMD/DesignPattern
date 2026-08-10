#pragma once
#include <iostream>
#include <vector>
#include <string>

/*观察者模式
* 一对多依赖
* 解耦
* 动态添加与删除
* 
* 优点:
* 1.发布者与订阅者解耦, 灵活可扩展
* 2.运行时可自由更改订阅关系
* 3.支持广播式通信
* 
* 缺点:
* 1.大量观察者可能带来性能开销
* 2.调试比较麻烦, 因为消息是间接触发的
* 
* 适用场景:
* 按键点击, 网络事件, ui事件
* 游戏内状态变化, ui更新, 数据绑定
*/

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void OnNotify(const std::string& message) = 0;
};

class Subject
{
public:
	void AddObserver(std::shared_ptr<IObserver> obs)
	{
		observers.push_back(obs);
	}

	void RemoveObserver(std::shared_ptr<IObserver> obs)
	{
		observers.erase(
			std::remove(observers.begin(), observers.end(), obs),
			observers.end()
		);
	}

	void Notify(const std::string& message)
	{
		for (auto obs : observers)
		{
			if (obs)
			{
				obs->OnNotify(message);
			}
		}
	}

private:
	std::vector<std::shared_ptr<IObserver>> observers;
};

class PlayerUI : public IObserver
{
public:
	virtual void OnNotify(const std::string& message) override
	{
		std::cout << "[PlayerUI] Received: " << message << std::endl;
	}
};

class AudioSystem : public IObserver
{
public:
	virtual void OnNotify(const std::string& message) override
	{
		std::cout << "[AudioSystem] Received sound trigger: " << message << std::endl;
	}
};
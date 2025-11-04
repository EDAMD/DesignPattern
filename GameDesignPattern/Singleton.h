#pragma once
#include <iostream>

/* 单例模式 - 确保一个类在系统中 仅有一个实例, 并且提供一个全局访问点 来获取该实例
* 1.保证全局只有一个对象管理某些资源或逻辑
* 2.节省内存开销(避免重复创建相同功能的对象)
* 3.提供统一访问接口, 方便管理
* 
* 使用场景:
* 管理全局状态(配置类管理, 日志系统, 资源管理器)
* 控制对某些唯一资源的访问(数据库链接, 线程池)
* 某些需要全局协调的组件(事件总线, 输入管理器)
*/
class Singleton
{
private:
	Singleton() { std::cout << "Singleton Created" << std::endl; }
	~Singleton() { std::cout << "Singleton Destory" << std::endl; }

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	static Singleton& GetInstance()
	{
		static Singleton instace;
		return instace;
	}

	void DoSomething()
	{
		std::cout << "Do Something in Singleton" << std::endl;
	}
};

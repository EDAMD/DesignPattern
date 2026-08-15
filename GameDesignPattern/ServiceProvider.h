#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

/*服务提供者模式
* 模块解耦, 降低耦合度
* 可扩展性
* 集中管理
* 
* 优点:
* 1.解耦
* 2.可扩展
* 3.集中管理
* 4.方便测试
* 
* 缺点:
* 1.引入全局状态, 可能增加调试复杂度
* 
* 适用场景:
* 游戏引擎服务容器: 日志, 网络, 配置, 资源管理
* 插件注册, 特定服务
* 
* UE：
* 模块接口注册: FMouduleManager::LoadModuleChecked()
* SubSystem
*/

class ILogger
{
public:
	virtual ~ILogger() = default;
	virtual void Log(const std::string& msg) = 0;
};

class ConsoleLogger : public ILogger
{
public:
	virtual void Log(const std::string& msg) override
	{
		std::cout << "[ConsoleLogger] " << msg << std::endl;
	}
};

class FileLogger : public ILogger
{
public:
	virtual void Log(const std::string& msg) override
	{
		std::cout << "[FileLogger] write to file: " << msg << std::endl;
	}
};


class ServiceProvider
{
public:
	template<typename T>
	void Register(const std::string& name, std::function<std::shared_ptr<T>()> creater)
	{
		creaters[name] = [creater]()
		{
			return std::static_pointer_cast<void>(creater());
		};
	}

	template<typename T>
	std::shared_ptr<T> Get(const std::string& name)
	{
		auto it = creaters.find(name);
		if (it != creaters.end())
		{
			return std::static_pointer_cast<T>(it->second());
		}
		return nullptr;
	}


private:
	std::unordered_map<std::string, std::function<std::shared_ptr<void>()>> creaters;
};

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <memory>

/*黑板模式
* 共享数据中心
* 模块解耦
* 统一信息来源
* 
* 优点:
* 1.模块低耦合
* 2.灵活扩展
* 3.集中化的数据状态管理
* 
* 缺点:
* 1.背板成为潜在全局共享状态, 容易被滥用
* 2.数据验证需要额外逻辑, 防止读取无效数据
* 3.数据更新的时序需要控制
* 
* 适用场景:
* 行为树, AI系统
* 集成控制, 仿真系统, 任务系统
* 
* UE: 行为树
*/

class Blackboard
{
public:
	using ValueType = std::variant<bool, float, std::string>;

	void SetValue(const std::string& key, ValueType value)
	{
		data[key] = value;
	}
	
	template<typename T>
	T GetValue(const std::string& key, const T& defaultValue = T())
	{
		auto it = data.find(key);
		if (it != data.end())
		{
			auto val = std::get_if<T>(&it->second);
			return *val;
		}
		return defaultValue;
	}

private:
	std::unordered_map<std::string, ValueType> data;
};

class AIAgent
{
public:
	AIAgent(std::shared_ptr<Blackboard> bb) :blackboard(bb) {}
	virtual void Tick() = 0;

protected:
	std::shared_ptr<Blackboard> blackboard;
};

class PerceptionSystem : public AIAgent
{
public:
	using AIAgent::AIAgent;

	virtual void Tick() override
	{
		blackboard->SetValue("EnemyVisible", true);
		blackboard->SetValue("EnemyDistance", 15.0f);
		std::cout << "[Perception] Enemy deteced Distance = 15" << std::endl;
	}
};

class AttackSystem : public AIAgent
{
public:
	using AIAgent::AIAgent;

	virtual void Tick() override
	{
		bool enemyVisible = blackboard->GetValue("EnemyVisible", false);
		float enemyDistance = blackboard->GetValue("EnemyDistance", 999.f);
		if (enemyVisible && enemyDistance < 20.f)
		{
			std::cout << "[Attack] Shooting enemy at distance: " << enemyDistance << std::endl;
		}
		else
		{
			std::cout << "[Attack] No target in range" << enemyDistance << std::endl;
		}
	}
};


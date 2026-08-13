#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

/*组件模式
* 组合优于继承
* 可插拔功能
* 高扩展性
* 解耦
* 
* 优点:
* 1.灵活的行为组合
* 2.易于扩展和复用
* 3.降低继承层级的复杂度
* 
* 缺点:
* 1.获取其他组件时可能需要查询
* 2.组件间通信需要设计接口
* 3.管理声明周期要谨慎
* 
* 适用场景
* 移动, 渲染, ai
* 运行时添加/移除工能模块
* 武器组合方式, 设计方式
* 后坐力组件
* 角色移动, 生命值, 特效, 动画
*/

class Component
{
public:
	virtual ~Component() = default;
	virtual void Update(float deltaTime) = 0;
};

class MovementComponent : public Component
{
public:
	virtual void Update(float deltaTime) override
	{
		std::cout << "[Movement] Moving entity by" << speed * deltaTime << "units." << std::endl;
	}

	void SetSpeed(float s) { speed = s; }

private:
	float speed;
};

class RenderComponent : public Component
{
public:
	virtual void Update(float deltaTime) override
	{
		std::cout << "[Render] Drawing entity on screen." << std::endl;
	}
};

class Entity
{
public:
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_shared<T>(std::forward<Args>(args)...);
		components.push_back(comp);
		return comp.get();
	}


	void Update(float deltaTime)
	{
		for (auto& comp : components)
		{
			comp->Update(deltaTime);
		}
	}


private:
	std::vector <std::shared_ptr<Component>> components;
};
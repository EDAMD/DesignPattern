#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <set>

/*ECS
* 数据与行为分离
* 灵活组合
* 高性能
* 易扩展
* 
* 优点:
* 1.代码解耦, 易维护
* 2.支持动态添加/移除组件
* 3.适合复杂游戏对象管理
* 
* 缺点:
* 1.设计复杂度较高
* 2.需要良好管理实体和组件声明周期
* 
* 适用场景:
* UI组件管理, 复杂状态管理
* 
* UE
* MassAI, 渲染
*/

namespace ECS
{
	struct Component
	{
		virtual ~Component() = default;
	};

	struct Position : public Component
	{
		float x, y;
		Position(float x = 0, float y = 0) : x(x), y(y) {}
	};

	struct Velocity : public Component
	{
		float vx, vy;
		Velocity(float vx = 0, float vy = 0) : vx(vx), vy(vy) {}
	};

	using Entity = int;

	class ComponentManager
	{
	public:
		void addPosition(Entity e, float x, float y)
		{
			positionComponents[e] = std::make_shared<Position>(x, y);
		}

		void addVelocity(Entity e, float x, float y)
		{
			velocityComponents[e] = std::make_shared<Velocity>(x, y);
		}

		Position* getPosition(Entity e)
		{
			auto it = positionComponents.find(e);
			if (it != positionComponents.end())
			{
				return  static_cast<Position*>(it->second.get());
			}
			return nullptr;
		}

		Velocity* getVelocity(Entity e)
		{
			auto it = velocityComponents.find(e);
			if (it != velocityComponents.end())
			{
				return  static_cast<Velocity*>(it->second.get());
			}
			return nullptr;
		}

		std::vector<Entity> getEntitiesWithPositionAndVelocity()
		{
			std::vector<Entity> result;
			for (auto& [e, pos] : positionComponents)
			{
				if (velocityComponents.find(e) != velocityComponents.end())
				{
					result.push_back(e);
				}
			}
			return result;
		}

	private:
		std::unordered_map<Entity, std::shared_ptr<Component>> positionComponents;
		std::unordered_map<Entity, std::shared_ptr<Component>> velocityComponents;
	};


	class System
	{
	public:
		virtual ~System() = default;
		virtual void Update(ComponentManager& cm, float dt) = 0;
	};

	class MovementSystem : public System
	{
	public:
		void Update(ComponentManager& cm, float dt) override
		{
			auto entities = cm.getEntitiesWithPositionAndVelocity();
			for (auto e : entities)
			{
				Position* pos = cm.getPosition(e);
				Velocity* vel = cm.getVelocity(e);

				pos->x += vel->vx * dt;
				pos->y += vel->vy * dt;

				std::cout << "[Entity_" << e << "] Move to [" << pos->x << ", " << pos->y << "]." << std::endl;
			}
		}
	};

}
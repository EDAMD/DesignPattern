#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>


/*HFSM - 分层状态机 (Hierachical Finite State Machine)
* 层级管理
* 
* 优点:
* 1.支持复杂行为分层管理
* 
* 缺点:
* 1.实现较复杂, 需要良好的设计
* 
* 适用场景:
* Animation, 网络协议, 机器人控制系统
* 
* UE：AnimStateMachine, AI, GAS
* 
* 核心思想	通过有限状态和事件驱动转换管理行为, HFSM支持状态层级嵌套
* 优点		结构清晰, 易维护, 支持复杂行为分层
* 缺点		状态多时设计复杂, HFSM实现难度较大
*/

namespace HFSM
{
	class State
	{
	public:
		virtual ~State() = default;

		virtual void enter()
		{
			for (auto& child : children)
			{
				child->enter();
			}
		}

		virtual void execute()
		{
			for (auto& child : children)
			{
				child->execute();
			}
		}

		virtual void exit()
		{
			for (auto& child : children)
			{
				child->exit();
			}
		}

		void addChild(std::shared_ptr<State> child)
		{
			children.push_back(child);
		}

		virtual std::string name() const = 0;

	protected:
		std::vector <std::shared_ptr<State>> children;
	};

	class ParentState : public State
	{
	public:
		virtual void enter() override
		{
			std::cout << "Enter Parent State" << std::endl;
			State::enter();
		}

		virtual void execute() override
		{
			std::cout << "Executing Parent State" << std::endl;
			State::execute();
		}

		virtual void exit() override
		{
			std::cout << "Exit Parent State" << std::endl;
			State::exit();
		}

		virtual std::string name() const override
		{
			return "Parent";
		}
	};

	class ChildState : public State
	{
	public:
		virtual void enter() override { std::cout << "Enter Child State" << std::endl; }
		virtual void execute() override { std::cout << "Executing Child State" << std::endl; }
		virtual void exit() override { std::cout << "Exit Child State" << std::endl; }
		virtual std::string name() const override { return "Child"; }
	};
}


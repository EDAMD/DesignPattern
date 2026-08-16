#pragma once

#include <iostream>
#include <memory>
#include <string>


/*FSM - 有限状态机 (Finite State Machine)
* 行为建模
* 状态管理
* 
* 优点:
* 1.结构清晰, 易于维护
* 2.便于扩展和调试
* 
* 缺点:
* 1.设计复杂度虽状态数量变多
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

namespace FSM
{
	class State
	{
	public:
		virtual ~State() = default;
		virtual void enter() = 0;
		virtual void execute() = 0;
		virtual void exit() = 0;
		virtual std::string name() const = 0;
	};

	class WalkingState : public State
	{
		virtual void enter() override { std::cout << "Enter Walking State" << std::endl; }
		virtual void execute() override { std::cout << "Walking..." << std::endl; }
		virtual void exit() override { std::cout << "Exit Walking State" << std::endl; }
		virtual std::string name() const { return "Walking"; }
	};

	class IdleState : public State
	{
		virtual void enter() override { std::cout << "Enter Idle State" << std::endl; }
		virtual void execute() override { std::cout << "Idle..." << std::endl; }
		virtual void exit() override { std::cout << "Exit Idle State" << std::endl; }
		virtual std::string name() const { return "Idle"; }
	};

	class FSM
	{
	public:
		void changeState(std::shared_ptr<State> newState)
		{
			if (currentState)
			{
				currentState->exit();
			}

			currentState = newState;

			if (currentState)
			{
				currentState->enter();
			}
		}

		void Update()
		{
			if (currentState)
			{
				currentState->execute();
			}
		}

		std::string getStateName() const
		{
			if (currentState)
			{
				return currentState ? currentState->name() : "None";
			}
		}
	private:
		std::shared_ptr<State> currentState;
	};
}
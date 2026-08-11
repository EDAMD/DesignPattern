#pragma once
#include <iostream>

using namespace std;

/*状态设计模式
* 
* 优点:
* 1.消除长 if-else / switch 语句
* 2.让状态切换更加清晰易维护
* 3.新增状态时不需要修改原有代码, 符合开闭原则
* 
* 适用场景:
* 运行时对象需要更改状态
* 
* UE:
* 动画状态机, AI行为, 网络连接
*/

class State
{
public:
	virtual ~State() = default;
	virtual void Handle() = 0;
};

class StateIdle : public State
{
public:
	virtual void Handle() override
	{
		cout << "角色处于待机状态" << endl;
	}
};

class StateRun : public State
{
public:
	virtual void Handle() override
	{
		cout << "角色处于奔跑状态" << endl;
	}
};

class CharacterState
{
public:
	void SetState(shared_ptr<State> state)
	{
		currentState = state;
	}

	void Update()
	{
		if (currentState)
		{
			currentState->Handle();
		}
	}
private:
	shared_ptr<State> currentState;
};
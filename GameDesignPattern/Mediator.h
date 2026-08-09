#pragma once
#include <iostream>
#include <vector>
#include <string>

/*中介者模式
* 解耦对象之间的复杂依赖
* 集中管理交互逻辑
* 可复用对象
* 
* 优点:
* 1.降低对象之间的耦合度
* 2.交互规则集中统一, 便于维护与修改
* 3.新增对象更容易, 不需要改动其他对象
* 
* 缺点:
* 1.中介者本身容易变得更加庞大, 承担过多逻辑
* 2.不适合交互种类特别多且复杂到难以统一抽象的场景
* 
* 适用场景:
* 多个对象的复杂通信, 通信逻辑高度统一
* 管理多个对象
* 聊天式, 消息总线
* UI控件之间的联动
*/

class Colleague;
class Mediator;

class Mediator
{
public:
	virtual ~Mediator() = default;
	virtual void Send(const std::string& message, Colleague* sender) = 0;
};

class Colleague
{
public:
	Colleague(Mediator& mediator) : mediator(mediator) {}

	virtual ~Colleague() = default;
	virtual void Receive(const std::string& message) = 0;

protected:
	Mediator& mediator;
};

class Player : public Colleague
{
public:
	Player(const std::string& name, Mediator& mediator) : Colleague(mediator), name(name) {}

	void SendMessage(const std::string& msg)
	{
		mediator.Send(msg, this);
	}

	virtual void Receive(const std::string& message) override
	{
		std::cout << "[Player " << name << "] received: " << message << std::endl;
	}
	
private:
	std::string name;
};

class GameMediator : public Mediator
{
public:
	void AddColleague(Player* colleague)
	{
		colleagues.push_back(colleague);
	}

	virtual void Send(const std::string& message, Colleague* sender) override
	{
		for (auto* colleague : colleagues)
		{
			if (colleague != sender)
			{
				colleague->Receive(message);
			}
		}
	}

private:
	std::vector<Player*> colleagues;
};
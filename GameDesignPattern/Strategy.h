#pragma once
#include <iostream>

using namespace std;

/*策略模式
* 封装算法簇
* 可自由切换算法
* 消除条件判断
* 
* 优点:
* 1.算法可以自由切换
* 2.符合开闭原则(增加策略而不修改原有代码)
* 3.复用性好, 解耦算法和调用方
* 
* 缺点:
* 1.增加了策略类的数量
* 2.客户端必须理解不同策略的区别后再选择
* 
* 适用场景:
* 场景中需要一种功能有多种算法, 
* 在运行时动态切换算法
* 避免大量条件语句的选择
* AI行为策略, 技能伤害公式, 
* 
* UE:
* ATask, Decoration, MovementComponent(切换运动状态)
*/

class IPaymentStrategy
{
public:
	virtual ~IPaymentStrategy() = default;
	virtual void Pay(int amount) = 0;
};

class PayByCreditCard : public IPaymentStrategy
{
public:
	virtual void Pay(int amount) override
	{
		cout << "Pay $" << amount << "using CREDIT CARD" << endl;
	}
};

class PayByPayPal : public IPaymentStrategy
{
public:
	virtual void Pay(int amount) override
	{
		cout << "Pay $" << amount << "using PAYPAL" << endl;
	}
};

class PaymentContext
{
public:
	void SetStrategy(shared_ptr<IPaymentStrategy> strategy)
	{
		this->strategy = strategy;
	}

	void Checkout(int amount)
	{
		if (strategy)
		{
			strategy->Pay(amount);
		}
		else
		{
			cout << "No payment strategy set." << endl;
		}
	}

private:
	shared_ptr<IPaymentStrategy> strategy;
};
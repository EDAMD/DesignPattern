#pragma once
#include <iostream>

/*外观模式 - 对复杂子系统提供简单接口
* 降低耦合
* 提高可维护性
* 
* 优点:
* 1.简化调用流程, 提高代码可维护性
* 2.让子系统更加容易使用, 降低学习成本
* 3.有助于分层架构设计
* 
* 缺点:
* 1.外观类可能成为"上帝对象", 承担过多责任
* 2.如果设计不当, 可能隐藏子系统的有用功能, 不够灵活
* 
* 使用场景:
* 1.封装复杂接口
* 2.分层架构
* 3.模块对外接口
* 
*/

class SubSystemA
{
public:
	void OperationA()
	{
		std::cout << "SubSystemA: Handling OperationA" << std::endl;
	}
};

class SubSystemB
{
public:
	void OperationB()
	{
		std::cout << "SubSystemB: Handling OperationB" << std::endl;
	}
};

class SubSystemC
{
public:
	void OperationC()
	{
		std::cout << "SubSystemC: Handling OperationC" << std::endl;
	}
};

class Facade
{
public:
	Facade()
	{
		a = new SubSystemA();
		b = new SubSystemB();
		c = new SubSystemC();
	}

	~Facade()
	{
		delete a;
		delete b;
		delete c;
	}

	void SimpleOperation()
	{
		std::cout << "[Facade] SimpleOperation Start !" << std::endl;
		a->OperationA();
		b->OperationB();
		c->OperationC();
		std::cout << "[Facade] SimpleOperation finished !" << std::endl;
	}

private:
	SubSystemA* a;
	SubSystemB* b;
	SubSystemC* c;
};


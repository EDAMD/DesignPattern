#pragma once
#include <iostream>

/*工厂模式 - 定义了一个创建对象的接口, 但由子类决定创建哪一种具体产品对象, 让他一个类的实例化推迟到子类进行
* 1.将对象创建和使用分离, 调用者不需要关系具体对象的构造细节
* 2.通过抽象工厂接口, 可以灵活扩展新的产品类型, 而不影响现有代码
* 3.方便统一管理对象的实例化逻辑
* 
* 使用场景:
* 1.对象的创建过程比较复杂, 需要封装起来
* 2.系统要根据不同条件创建不同类型的对象
* 3.产品类结构较稳定, 而具体实例化的细节可能变动
* 3.希望代码对新增的产品类型具有扩展性, 而不修改现有逻辑
* 
* 应用方向:
* 1.日志记录系统(根据配置, 选择不同输出方式. 例如控制台/文件/网络)
* 2.游戏实体创建(敌人类型, 关卡物体, 技能对象)
* 3.跨平台资源加载(不同平台需要不同实现)
*/

class Product
{
public:
	virtual void Use() = 0;
	virtual ~Product() = default;
};

class ProductA : public Product
{
public:
	void Use() override
	{
		std::cout << "Using ProductA" << std::endl;
	}
};

class ProductB : public Product
{
public:
	void Use() override
	{
		std::cout << "Using ProductB" << std::endl;
	}
};

class Factory
{
public:
	virtual std::unique_ptr<Product> CreateProduct() = 0;
	virtual ~Factory() = default;
};

class FactoryA : public Factory
{
public:
	std::unique_ptr<Product> CreateProduct() override
	{
		return std::make_unique<ProductA>();
	}
};

class FactoryB : public Factory
{
public:
	std::unique_ptr<Product> CreateProduct() override
	{
		return std::make_unique<ProductB>();
	}
};
